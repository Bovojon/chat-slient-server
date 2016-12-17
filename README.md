# chat-slient-server

>> Based on [Socket programming in C on Linux](http://www.binarytides.com/socket-programming-c-linux-tutorial/) tutorial

## Sockets
* Sockets are the virtual endpoints of any kind of networks communications.

* `inet_ntoa()` converts IP addresses in long format to dotted notation.

* `inet_addr()` converts IP addresses in dotted notation to long format.

* `bind()` is used to bind a socket to a particular "address and port" combination - this ensures that all incoming data which is directed towards this port number is received by this application. Thus 2 sockets cannot be bound to the same port.
