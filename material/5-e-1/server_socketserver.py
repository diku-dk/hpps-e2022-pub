
import argparse
import socketserver
import time

from typing import Tuple

SERVER_IP = "127.0.0.1"
SERVER_PORT = 5678
MSG_MAX_SIZE = 256


# Here we have created a custom server type. Currently it just calls the parent
# class ThreadingTCPServer. If we wanted to add any specific functionality to
# the server itself, we would modify this class
class MyServer(socketserver.ThreadingTCPServer):
    def __init__(self, server_address: Tuple[str, int], name: str,
                 request_handler_class):
        """
        Constructor for MyServer
        :param server_address: IP address and Port number to host server at
        :param request_handler_class: Handler for responding to requests
        """
        super().__init__(server_address, request_handler_class)
        self.name = name
        print(f"MyServer '{name}' has started")


class MyHandler(socketserver.StreamRequestHandler):
    """
    A handler class to process all messages sent to the server
    """

    def handle(self) -> None:
        """
        This is the initial function, called by the handler for every message.
        Will always respond to every message.
        :return: No return
        """
        # We use a try/except here to make sure that even if something goes
        # wrong in our server, we always return a response
        try:
            print(f"Server messaged by {self.client_address}")

            # Technically we do not need to perform this check as we can keep
            # track of what servers we are running with what handlers, but its
            # always good practice to check
            if not isinstance(self.server, MyServer):
                self.handle_error("Invalid server type to handle this request")
                return

            bytes_message = self.request.recv(MSG_MAX_SIZE)

            if not bytes_message:
                self.handle_error(f"No bytes received.")
                return

            string_message = bytes_message.decode('utf-8')

            response = \
                bytearray(f"Message '{string_message}' received".encode())
            self.request.sendall(response)

            # Uncomment this line to add a delay to message processing
            # time.sleep(10)
            print(f"Server responded to '{self.client_address}'")

            return
        except Exception as e:
            self.handle_error(f"An error was encountered in the server. {e}")

    def handle_error(self, error_msg: str) -> None:
        """
        Function to send error messages back to the client
        :param error_msg: An error message to print. This is not returned to
        the client, but a generic error message is
        :return: No return
        """
        print(f"{error_msg}")
        # Note that we are not telling the client what went wrong. This is
        # often a good security consideration as malicious actors could use
        # this info to work out what our server does and how it works
        response = bytearray("Internal server error".encode())
        self.request.sendall(response)
        return


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "name",
        help="Name of the server, e.g.: TestServer")
    args = parser.parse_args()

    # Here we start a server running on the localhost at port 5678
    with MyServer((SERVER_IP, SERVER_PORT), args.name, MyHandler) as my_server:
        try:
            # Run this server until we specifically tell it to shutdown
            my_server.serve_forever()
        finally:
            # Shutdown our server if we ever call this script by hitting Ctrl+C
            my_server.server_close()
