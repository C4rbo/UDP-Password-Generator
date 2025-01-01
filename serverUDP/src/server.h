#ifndef SERVER_H
#define SERVER_H

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
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants
#define PORT 57015
#define BUFFMAX 255
#endif
