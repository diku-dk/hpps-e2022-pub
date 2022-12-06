# Practical
Just some pratical work today. A Python client has been provided for you, which will attempt to contact a server and retrieve 2 files, one small and one large. Your task is to implement a server, capable of responding to those messages. A framework has been provided for you to implement your server in, with you only needing implement a response generator in as many or as few functions as are neceessary. 

Do note that a key part of this protocol is that no message will ever exceed 1024 bytes in length. You will need to identify when your message requires more than this length and split up your responses accordingly.

## Protocol
All messsages from the client to the server must contain the same header as follows:

    4 bytes - Length of request data, excluding this header, unsigned integer in network byte-order

An additional field of the length given in the header will also be present. This is a path to the requested file to be retrieved.

Regardless of the message type, a response will ALWAYS be expected from the server.

All replies from the server to the client must contain the same header as follows:

    4 bytes - Length of response data, excluding this header, unsigned integer in network byte-order
    4 bytes - Status Code of the response, unsigned integer in network byte-order
    4 bytes - Block number, a zero-based count of which block in a potential series of replies this is, unsigned integer in network byte-order
    4 bytes - Block count, the total number of blocks to be sent, unsigned integer in network byte-order
    32 bytes - Block hash, a hash of the response data in this message only, as UTF-8 encoded bytes
    32 bytes - Total hash, a hash of the total data to be sent across all blocks, as UTF-8 encoded bytes

In addition to the header each response will include an additional payload of the length given in the header. Note that in the case of a small enough response to only require a single reply, then the block hash and total hash will be identical. If the response is to a request for data file, and it could be retrieved with no errors then the payload will be either all or part of said file, depending on the size of the file. In all other cases the response will be a feedback message explaining any errors or results of other querries.

The following error codes may be provied by the server:

    1 - OK (i.e. no problems encountered)
    2 - Bad Request (i.e. the request is coherent but cannot be servered as the file doesn't exist)
    3 - Malformed (i.e. the request is malformed and could not be processed)
    4 - Other (i.e. any error not covered by the other status codes) 
