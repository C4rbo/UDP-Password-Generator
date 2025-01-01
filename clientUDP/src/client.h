#ifndef CLIENT_H
#define CLIENT_H

#if defined WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#define close closesocket
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#endif

#include <stdio.h>
#include <stdlib.h>

// Constants
#define SERVER_NAME "passwdgen.uniba.it"
#define PORT 57015
#define BUFFMAX 255

#endif
