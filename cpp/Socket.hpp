#ifndef SOCKET_H
#define SOCKET_H

#include <string>
// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

// research netdb.h
#include <netdb.h>

#define PORT 8080
#define MAXLINE 256


// 

using namespace std;

class Socket {
	public:
		Socket();
		Socket(uint16_t port);

		virtual ~Socket();
		int sockfd;
		char buffer[MAXLINE];
		bool initialized;
		uint8_t socketFamily;
		uint16_t inAddr;
		uint16_t port;
		struct sockaddr_in servaddr;
		struct sockaddr_in cliaddr;
		

		long receive(char *buffer, int max_size);
		long receive_ex(uint8_t *buffer, int max_size);
	
	private:

		long send(char *msg);
		double myPrivateMethod() {
			return 1.0;
		}
	
	

};

#endif
