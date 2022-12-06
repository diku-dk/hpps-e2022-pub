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

        pass

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
