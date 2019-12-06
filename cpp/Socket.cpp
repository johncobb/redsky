/**
 * @file Socket.cpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

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
    
    memset(buffer, '0', sizeof(buffer));
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

    initialized = true;
}

long Socket::receive(uint8_t *buffer, unsigned long max_size) {
    socklen_t len;

    // reset buffer
    memset(buffer, 0, max_size);
    
    long bytes = (long) recvfrom(sockfd, buffer, max_size, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
    
    // let's have some fun here and convert s_addr to a human readable ip
    // todo: optimize this away into diagnostics loggin that can be toggled
    // on and off when an observer attaches to diagnostics port
    char ip[12];
    memset(ip, 0, 12);

    strcpy(ip, (char*)inet_ntoa((struct in_addr)cliaddr.sin_addr));

    cout << "Socket: " << ip << ":" << cliaddr.sin_port << endl;

    return bytes;
}


long Socket::send(char *msg) {
    return sendto(sockfd, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, sizeof(msg)); 
}

Socket::~Socket() {

}
