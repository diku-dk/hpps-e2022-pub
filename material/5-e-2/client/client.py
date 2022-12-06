#!/bin/python3

import os
import socket
import struct

# This is quick hack to get relative imports of a higher file working 
if __package__ is None:
    import sys
    sys.path.append(
        os.path.dirname(os.path.dirname( os.path.abspath(__file__)))
    )

from shared import *

class Server(object):
    def __init__(self, ip: str, port: int):
        """
        Constructor for custom Server object

        ip(str): IP address for remote server
        port(int): Port number of remote server
        """
        self.ip = ip
        self.port = port

    def send_to_server(self, request: bytes) -> bytes:
        """
        Function to send a message to the defined server

        request(bytes): The message to send

        This function assumes the server is already listening at the address 
        specified by the constructor. The provided request is sent to the 
        server and a response is always expected, even in the case of errors.
        The response message data is always returned. In the case of multiple 
        blocks of response, all blocks are combined into a single return value.
        """
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as conn_socket:
            # Connect and send message
            conn_socket.connect((self.ip, self.port))
            conn_socket.sendall(request)

            responding = True
            all_blocks = None

            # Note loop here for processing messages of several blocks. 
            # Students may wish to have two seperate implementations, one for 
            # blocked messages and one for message that can be entirely read 
            # within a single block. That is acceptable, but they should be 
            # encouraged to solve it propperly (e.g. one function for both)
            while responding:
                # Read just enough bytes to get the length of this response
                inital_read = conn_socket.recv(LEN_RESPONSE_LENGTH)
                response_length = struct.unpack('!I', inital_read)[0]

                # Now read the expected number of bytes
                response_bytes = conn_socket.recv(
                    response_length+LEN_STATUS+LEN_BLOCK_ID+LEN_BLOCKS_COUNT
                    +LEN_BLOCK_HASH+LEN_TOTAL_HASH)

                # Parse the individual message attributes
                status = struct.unpack('!I', response_bytes[
                    0
                    :LEN_STATUS
                ])[0]
                this_block = struct.unpack('!I', response_bytes[
                    LEN_STATUS
                    :LEN_STATUS+LEN_BLOCK_ID
                ])[0]
                total_blocks = struct.unpack('!I', response_bytes[
                    LEN_STATUS+LEN_BLOCK_ID
                    :LEN_STATUS+LEN_BLOCK_ID+LEN_BLOCKS_COUNT
                ])[0]
                block_checksum = response_bytes[
                    LEN_STATUS+LEN_BLOCK_ID+LEN_BLOCKS_COUNT
                    :LEN_STATUS+LEN_BLOCK_ID+LEN_BLOCKS_COUNT+LEN_BLOCK_HASH
                ]
                total_checksum = response_bytes[
                    LEN_STATUS+LEN_BLOCK_ID+LEN_BLOCKS_COUNT+LEN_BLOCK_HASH
                    :LEN_STATUS+LEN_BLOCK_ID+LEN_BLOCKS_COUNT+LEN_BLOCK_HASH
                        +LEN_TOTAL_HASH
                ]
                response = response_bytes[
                    LEN_STATUS+LEN_BLOCK_ID+LEN_BLOCKS_COUNT+LEN_BLOCK_HASH
                        +LEN_TOTAL_HASH
                    :LEN_STATUS+LEN_BLOCK_ID+LEN_BLOCKS_COUNT+LEN_BLOCK_HASH
                        +LEN_TOTAL_HASH+response_length
                ]

                # Setup container for all blocks to be assembled together
                if all_blocks == None:
                    all_blocks = [None] * total_blocks

                # Report any unexpected feedback
                if status != STATUS_OK:
                    msg = f"Got unexpected status code: {status}"
                    print(msg)
                    all_blocks[this_block] = msg
                    continue

                # Report hash inconsistencies
                if get_sha256(response) != block_checksum:
                    msg = f"Block {this_block}/{total_blocks} checksums for " \
                        "a block did not match"
                    print(msg)
                    all_blocks[this_block] = msg
                    continue

                # Add this response to the all_blocks container
                all_blocks[this_block] = response

                # Report how many more blocks we are expecting
                count = len(all_blocks) - all_blocks.count(None)
                print(f"block: {this_block} ({count}/{len(all_blocks)})")

                # If we have all the blocks, then finish the loop
                if all_blocks.count(None) == 0:
                    responding = False
            
            # Check hash of all the data 
            all_data = b"".join(all_blocks)
            if get_sha256(all_data) != total_checksum:
                print("Total checksum for all data did not match")

            return all_data

def to_server(payload: bytes, configs: dict):
    """
    Function to send a message to a server

    payload(bytes): The message to send
    config(dict): Configuration options defining server location

    The payload is sent to the server, with any response either printed or
    written directly to file depending on the request. No value is returned.
    """
    # Connect to the remote server
    server = Server(configs['server_ip'], configs['server_port'])

    data = server.send_to_server(payload)

    # Where, if anywhere any output should be written
    local_path = payload[LEN_REQUEST_LENGTH:] \
        .decode('utf-8')

    # If we are not expecting any data files to be written, then print the
    # output of the request
    if not local_path or local_path[-1] == os.path.sep:
        print(f"Got response: {data.decode('utf-8')}")

    # Data files are written straight to file rather than printing
    else:
        with open(local_path, "wb") as binary_file:
            binary_file.write(data) 

        print(f'Retrieved data written to {local_path}')

    return


def assemble_payload(request: str):
    """
    Funtion to create a bytearray message out of the provided argument.
    """    

    payload = bytearray()
    payload.extend(struct.pack('!I', len(request)))
    payload.extend(bytes(request, "utf-8"))

    return payload
  

if __name__ == "__main__":
    configs = {
        "server_ip": "127.0.0.1",
        "server_port": 12345,
        "client_ip": "127.0.0.1",
        "client_port": 23456
    }
        
    # Retrieve the smaller file
    to_server(
        assemble_payload('tiny.txt'), 
        configs
    )

    # Retrieve the larger file that will be broken into blocks
    to_server(
        assemble_payload('hamlet.txt'),
        configs
    )
