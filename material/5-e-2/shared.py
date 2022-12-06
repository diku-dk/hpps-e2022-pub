import hashlib
import string
import random

# Max length of any individual message. Note this has been arbitrarily set for
# this assignment and is not meant to reflect any real world limit.
MSG_MAX = 1024

# The fixed lengths of various message attributes
LEN_REQUEST_LENGTH = 4
LEN_RESPONSE_LENGTH = 4
LEN_STATUS = 4
LEN_BLOCK_ID = 4
LEN_BLOCKS_COUNT = 4
LEN_BLOCK_HASH = 32
LEN_TOTAL_HASH = 32

# Response status codes
STATUS_OK = 1
STATUS_BAD_REQUEST = 2
STATUS_MALFORMED = 3
STATUS_OTHER = 4

def get_sha256(data: bytes) -> str:
    """
    Function to get the SHA256 hash of some given data.
    
    data(bytes): The data to hash.

    Returns the hash of the given data as a str.
    """
    return hashlib.sha256(data).digest() 

