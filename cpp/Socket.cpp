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

	// Bind the socket with the server address 
	// if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) {
    //     throw "Socket bind failed.";
	// } 
 	if ( bind(sockfd, (struct sockaddr *)&servaddr, sizeof(Socket::servaddr)) < 0 ) {
        throw "Socket bind failed.";
	}   
}

long Socket::receive(char *buffer, int max_size) {
    socklen_t len;
    socklen_t n;

    // n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
    memset(buffer, '0', max_size);

    n = recvfrom(sockfd, buffer, max_size, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
    if (n > 0) {

        cout << "bytes: " << n << endl;


        // std::hex << buffer[0] << buffer[1] << buffer[2] << buffer[3];

        // hex << buffer[0];

        // cout << endl;

    }

    return n;

}

long Socket::send(char *msg) {
    return sendto(sockfd, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, sizeof(msg)); 
}

Socket::~Socket() {
}
