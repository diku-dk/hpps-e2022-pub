#!/bin/python3

import os
import socketserver
import struct
import math

# This is quick hack to get relative imports of a higher file working 
if __package__ is None:
    import sys
    sys.path.append(
        os.path.dirname(os.path.dirname( os.path.abspath(__file__)))
    )

from shared import *

class ExerciseServer(socketserver.ThreadingTCPServer):
    def __init__(self, configs: dict, 
            request_handler_class: socketserver.StreamRequestHandler):
        """
        Constructor for ExerciseServer.

        configs(dict): Configuration dictionary of for the server. Must include
            entires for 'server_ip', and 'server_port'.
        request_handler_class(socketserver.StreamRequestHandler): A handler to
            reespond to any messages sent to this server.

        This server inherits from the socketserver.ThreadingTCPServer. It makes
        no changes and is just here as a reference
        """
        super().__init__((configs['server_ip'], configs['server_port']), 
            request_handler_class)


class RequestHandler(socketserver.StreamRequestHandler):
    """
    Custom handler to handle any inbound messages. Any input message will 
    ALWAYS receive an appropriate response.
    """

    def handle(self):
        """
        Function to initially handle any requests received. 
        
        This will read a request, perform some curseory validation before 
        calling more specific handling functions. Nothing is returned.
        """
        try:
            # Read request
            bytes_message = self.request.recv(MSG_MAX)

            # Extract request attributes
            request_length = struct.unpack('!I', bytes_message[
                0
                :LEN_REQUEST_LENGTH
            ])[0]
            request = bytes_message[
                LEN_REQUEST_LENGTH
                :LEN_REQUEST_LENGTH + request_length
            ]

            # Validate message length
            if len(request) != request_length:
                self.handle_error(
                    STATUS_MALFORMED,
                    "Malformed request. Length of request does not match "
                    "given length"
                )

            self._handle_request(request)
 
        # Always generate a response, this is the fallback for if all other
        # validation and handling fails. This is acceptable as a last resort,
        # but were possible more helpful feedback and responses should be 
        # generated.
        except Exception as e:
            self.handle_error(STATUS_OTHER, f"Something went wrong. {e}")

    def _handle_request(self, request:bytes) -> None:
        """
        Function to handle a 'get file' type request.
        request(bytes): The request message body

        A data file is read and sent back to the requestee. A response is 
        always generated, either the data file or an error message explaining 
        what went wrong.
        """

        get_path = request.decode("utf-8")

        # Process domain from top header line. If it starts with a path
        # separator, remove it. Without doing this the path will go to the root
        # directory of the server host, rather than the servers base folder.
        if get_path[0] == os.path.sep:
            get_path = get_path[1:]

        # Report a request for missing data
        if not os.path.exists(get_path):
            self.handle_error(
                STATUS_BAD_REQUEST,
                f"Requested content {get_path} does not exist")
            return

        data = ""

        # Report request for nonsense data
        if not os.path.isfile(get_path):
            self.handle_error(
                STATUS_BAD_REQUEST,
                f"Request URI {get_path} is not a file")
            return

        # Get file data as bytes
        with open(get_path) as requested_file:
            data = requested_file.read()
        if type(data) != bytes:
            data = bytes(data, "utf-8")

        # Send a response
        print(f'Sending requested data from {get_path}')
        self._build_and_send_responses(STATUS_OK, data)
        return

    def handle_error(self, status:int, msg_str: str) -> None:
        """
        Function to handle any errors that are encountered during request 
        handling and response processing. 
        
        status(int): A status code describing the error encountered.
        msg_str(str): A more descriptive response detailing exactly what went 
            wrong

        Will print a message to the server command line, and return an 
        appropriate response to the requesting client.        
        """
        print(msg_str)
 
        self._build_and_send_responses(status, bytes(msg_str, "utf-8"))

        return

    def _build_and_send_responses(self, status:int, to_send: bytes) \
            -> bytearray:
        """
        Function to build a response and send it.

        status(int): The response status code. Should reflect the content of
            the message itself
        to-send(bytes): The response message body.

        The provided attributes are assembled into a bytes message according to
        the protocol described in the handout. Various attributes such as the
        payload length are dynamically calculated. If the message is longer 
        than the set message limit, then the payload is broken into blocks and
        sent seperately until all blocks have been sent.
        """
        # Get chechsum of the total message data to send
        total_checksum = get_sha256(to_send)
        # Calculate how long the payload can be, as we have a set limit of how
        # many bytes can be sent, and a header that must be attatched to each
        # message.
        sendable_length = MSG_MAX-LEN_RESPONSE_LENGTH-LEN_STATUS-LEN_BLOCK_ID \
            -LEN_BLOCKS_COUNT-LEN_BLOCK_HASH-LEN_TOTAL_HASH

        blocks = math.ceil(len(to_send) / sendable_length)
        this_block = 0

        # loop to send one or more blocks of payload
        while len(to_send) > 0:

            this_payload = to_send[:sendable_length]

            # Assemble an individual payload block
            payload = bytearray()
            payload.extend(struct.pack('!I', len(this_payload)))
            payload.extend(struct.pack('!I', status))
            payload.extend(struct.pack('!I', this_block))
            payload.extend(struct.pack('!I', blocks))
            payload.extend(get_sha256(this_payload))
            payload.extend(total_checksum)    
            payload.extend(this_payload)

            print(f"Sending reply {this_block}/{blocks} with payload length "
                f"of {len(this_payload)} bytes")

            # Send the block
            self.request.sendall(payload)

            # Determine if more blocks to send
            to_send = to_send[sendable_length:]
            this_block = this_block + 1

if __name__ == "__main__":
    configs = {
        "server_ip": "127.0.0.1",
        "server_port": 12345,
    }    
    
    # This check is not a formal requirement of the system but should let you 
    # know if you've started your server in the wrong place. Do feel free to 
    # change or remove this if you are wanting to use different data files
    for f in ["tiny.txt", "hamlet.txt"]:
        if not os.path.isfile(f): 
            print(f"Server can't find expected data file {f}. Make sure you " + 
                  "are starting the server with the files next to it in the " + 
                  "directory")
            exit(1)

    print(f"Starting server at: {configs['server_ip']}:"
        f"{configs['server_port']}")
    with ExerciseServer(configs, RequestHandler) as exercise_server:
        try:
            exercise_server.serve_forever()
        finally:
            exercise_server.server_close()
