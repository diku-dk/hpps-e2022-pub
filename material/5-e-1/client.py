import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 5678
MSG_MAX_SIZE = 256


def send_to_server(message: str) -> None:
    """
    Function to communicate with a server. Send a message to it and print the
    response
    :param message: A string message to send
    :return: No return
    """
    # Set up a client socket. By using a 'with' statement we can leave out
    # explicitly closing the connection, as this will be done automatically
    # once the with statement completes
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        # Connect this socket to the given IP and PORT. Note these are the
        # same as where we have run the server, as that is what we wish to
        # connect to
        client_socket.connect((SERVER_IP, SERVER_PORT))

        # Assemble the request as a series of bytes and send along the
        # connection
        request = bytearray(message.encode())
        client_socket.sendall(request)

        # Receive a response and print it
        response = client_socket.recv(MSG_MAX_SIZE)
        print(response)

        # This line is not strictly necessary due to the with statement, but
        # has been left here to illustrate the complete socket lifespan
        client_socket.close()


if __name__ == "__main__":
    # Send a message to a server
    send_to_server("This is a message")
