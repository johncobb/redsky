#include "Socket.hpp"
#include <iostream>

using namespace std;

// for now keep the follwing
#ifndef MSG_CONFIRM
#define MSG_CONFIRM 0
#endif

Socket::Socket() {

}

Socket::Socket(uint16_t port):port(port)  {
    
    initialized = true;

    // memset(buffer, '0', sizeof(buffer));

    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port); 

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 

        throw "Socket creation failed.";
    }
    
 	if ( bind(sockfd, (struct sockaddr *)&servaddr, sizeof(Socket::servaddr)) < 0 ) {
        throw "Socket bind failed.";
	}   
}

long Socket::receive(uint8_t *buffer, int max_size) {
    socklen_t len;
    socklen_t n;

    memset(buffer, 0, max_size);

    n = recvfrom(sockfd, buffer, max_size, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);

    return n;    
}

long Socket::send(char *msg) {
    return sendto(sockfd, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, sizeof(msg)); 
}

Socket::~Socket() {
}
