These exercises are contained in two parts, a few theory questions and some programming tasks. The programming
tasks should act a as a good basis for the networking coursework, whilst the theory may be more of an introduction
to exam style questions.

## Practical

Within this folder you should find three Python files deomonstrating some simple network communication.
The first of these will run a client that will send a message across a network and wait for a response.
It can be run using the command:
   
   Python3 client.py

If you do not run the server first. Your client will not work as it has nothing to connect to. 
There are two options or running a server process. First is server_socket.py, which uses the socket 
library to listen for inbound cimmunications and then echo them back. It can be started with:

    Python3 server_socket.py ServerName

Finally is server_socketserver.py. This is a more robust server implementation using the socketserver 
library. This library builds upon the socket library to provide robust base implementations for servers
and is the defacto library for implementing them in Python. If we were limited to using C we would
have to stick with using base socket programming, but this can get tedious and is more prone to errors.
To start server_socketserver.py we can type:

    Python3 server_socketserver.py ServerName

You can stop the server by hitting Ctrl+C. Note that here we give the server a name. This is not necessary
for servers usually, but has been provided here as an example of how we can define certain characteristics
of out server from command line arguments.

Your task at this exercise is to familiarise with Python, or brush up on your skills before A4 as 
it is a Python based network programming task. Initially you should investigate server_socket.py. 

    1) Start multiple clients each connecting to the same server_socket at the same time. You may need to 
       add a delay to the message processing to be able to do this. What happens when a message is
       recieved before the previous one is completed? What effect might this have on server performance? 
       What effect would it have on client performance?
       
You should now investigate server_socketserver.py. 

    2) Add delays in the same manner as before and connect multiple clients. What happens here? How would
       This alter performance for the client and server compared to the server_socket?
    
Continue to investigate server_socketserver. Make sure to remove any delaying timers from the last exercise
as they will just slow things down unnecessarily for these subsequent parts.

### Ping/pong
When modify the client so that it takes user input from the command line as the messages to send. Modify the server so that if it receives a `ping` message, it replies with a `pong`. In all other cases the server returns `BAD REQUEST`.

### Distributed variable
Modify the server again so that it takes two different kinds of messages:

* `PUT [SOME STRING]` that stores a string in the internal storage of the server. Note that the first space is a separator and thus part of the protocol syntax.
* `GET` that returns the string that is stored.

When the server receives a `PUT` it saves the string to an internal variable and returns `OK`. The following `PUT` messages will not update the variable, but return `VARIABLE FILLED`.

When the server receives a `GET` it returns the stores variable. All `GET`s should be blocking, until the server has received the first `PUT`. Thus, clients sending a `GET` before another client send a `PUT` should block and wait until the server receives the first `PUT` and responds to all waiting clients.

## Theory
These exercises are completely optional, but could be a good guide for the sort of knowledge we 
may expect in any future exams... 

1) Why are standards important for protocols?

2) Suppose Host A wants to send a large file to Host B. The path from Host A to Host B has 
    three links, of rates R1=500 kbps, R2=2 Mbps, and R3=1 Mbps.
        a) Assuming no other traffic in the network, what is the throughput for the file 
            transfer?
        b) Suppose the file is 4 million bytes. Dividing the file size by the throughput, 
            roughly how long will it take to transfer the file to Host B?
        ) c. Repeat (a) and (b), but now with R reduced to 100 kbps.

3) An application using UDP to send messages typically only needs one socket, whereas a 
    similar application using TCP would need needed two sockets. Why? If the TCP server were 
    to support n simultaneous connections, each to a different host, how many sockets would 
    the TCP based application need?
    
4) In modern packet-switched networks, including the Internet, the source host segments
    long, application-layer messages (for example, an image or a music file) into smaller packets
    and sends the packets into the network. The receiver then reassembles the packets back into
    the original message. We refer to this process as message segmentation. Consider a
    message that is bits 10⁶ long that is to be sent from source to destination. Suppose there
    are 3 links, and each is 2 Mbps. Ignore propagation, queuing, and processing delays.
     a) Consider sending the message from source to destination without message
        segmentation. How long does it take to move the message from the source host to the
        first packet switch? Keeping in mind that each switch uses store-and-forward packet
        switching, what is the total time to move the message from source host to destination
        host?
     b) Now suppose that the message is segmented into 800 packets, with each packet being
        10,000 bits long. How long does it take to move the first packet from source host to the
        first switch? When the first packet is being sent from the first switch to the second switch,
        the second packet is being sent from the source host to the first switch. At what time will
        the second packet be fully received at the first switch?
     c) How long does it take to move the file from source host to destination host when
        message segmentation is used? Compare this result with your answer in part (a) and
        comment
     d) In addition to reducing delay, what are reasons to use message segmentation?
     e) Discuss the drawbacks of message segmentation.

## Theory solutions

The solutions to the above exercises are provided here, though you are encouraged to properly
attempt them bfeore you look here

1) Standards are important for protocols so that people can create networking systems and products that interoperate. Without a standard noone would agree how to communicate
   
2)  a) 500 kbps 
    b) 64 seconds
    c) 100kbps; 320 seconds
    
3) With a UDP server, there is no welcoming socket, and all data from different clients  enters the server through this one socket. With the TCP server, there is a welcoming socket, and each time a client initiates a connection to the server, a new socket is created. Thus, to support n simultaneous connections, the server would need n+1 sockets.
    
4)  a) 4 sec to first, 12 sec in total
    b) 5 ms to first, 10 ms for second
    c) Time at which 1st packet is received at the destination host =
        5 m sec * 3 hops = 15 m sec. After this, every 5msec one packet will be received; thus time at which last (800th) packet is received = 15 m sec + 799 * 5m sec = 4.01 sec . It can be seen that delay in using message segmentation is significantly less (almost 1/3rd). 
    d) Without message segmentation, if bit errors are not tolerated, if there is a single bit error, the whole message has to be retransmitted (rather than a single packet). Without message segmentation, huge packets (containing HD videos, for example) are sent into the network. Routers have to accommodate these huge packets. Smaller packets have to queue behind enormous packets and suffer unfair delays.
    e) Packets have to be put in sequence at the destination.         Message segmentation results in many smaller packets. Since header size is usually the same for all packets regardless of their size, with message segmentation the total amount of header bytes is more.
