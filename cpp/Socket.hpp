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

#define PORT 8080
#define MAXLINE 1024
#define MSG_CONFIRM 0


class Socket {
	public:
		Socket();
		Socket(const Socket& sck);
		virtual ~Socket();
		std::string name;

		int socketfd;
		char buffer[MAXLINE];
		std::string endpointAddress = "";
		// struct socketaddr_in servaddr;
		// struct socketaddr_in cliaddr;
		

		void setEndpointAddress(std::string endpoint) {
			endpointAddress = endpoint;
		}

		std::string getEndpointAddress() {
			return endpointAddress;
		}

		uint32_t connect() {
			
		}


	private:

	double myPrivateMethod() {
		return 1.0;
	}

};

#endif
