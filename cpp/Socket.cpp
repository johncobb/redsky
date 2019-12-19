/**
 * @file Socket.cpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#include <iostream>
#include <sys/types.h>
#include <sys/select.h>
#include "Socket.hpp"


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

void Socket::enableSelect() {
    FD_ZERO(&master);
    FD_SET(sockfd, &master);
}

long Socket::receiveFromSelect(uint8_t *buffer, int max, endpoint_t *info) {

    long bytes = 0;

    int select_val = select(sockfd+1, &master, nullptr, nullptr, nullptr);

    /* select_val 0: timeout select_val -1: error */
    if (select_val > 0) {
        socklen_t len;

        // reset buffer
        memset(buffer, 0, max);
        
        bytes = (long) recvfrom(sockfd, buffer, max, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);

        if (bytes < 0) {
            throw "Socket recvfromselect failed.";
        }  

        if (info != NULL) {
            info->addr.sin_addr = cliaddr.sin_addr;
            info->addr.sin_port = cliaddr.sin_port;
            info->len = bytes;
            info->timestamp = clock();
        }

    } else if (select_val == 0) {
        throw "Socket receivefrom timeout.";
    } else if (select_val == -1) {
        throw "Socket error.";
    }

    return bytes;  
}

// using this receiveFrom prevents us from sending a response
// as we do not record the client address
long Socket::receiveFrom(uint8_t *buffer, int max) {

    return receiveFrom(buffer, max, NULL);
}

long Socket::receiveFrom(uint8_t *buffer, int max, endpoint_t *info) {
    socklen_t len;

    // reset buffer
    memset(buffer, 0, max);
    
    long bytes = (long) recvfrom(sockfd, buffer, max, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
    
    if (bytes < 0) {
        throw "Socket recvfrom failed.";
    }
    
    if (info != NULL) {
        info->addr.sin_addr = cliaddr.sin_addr;
        info->addr.sin_port = cliaddr.sin_port;
        info->len = bytes;
        info->timestamp = clock();
    }



    return bytes;    
}



// todo: research returning from function vs passing argument
// sockaddr_in Socket::receiveFrom(uint8_t* buffer, int max, int flags) {
//     socklen_t len;
//     sockaddr_in from;
//     int size = sizeof(from);

//     // int ret = recvfrom(sockfd, buffer, len, flags, reinterpret_cast<SOCKADDR *>(&from), &size);
//     int ret = recvfrom(sockfd, buffer, max, flags, ( struct sockaddr *) &from, &len);
//     buffer[ret] = 0;
//     return from;

// }

void Socket::send(const char* data, int len, sockaddr_in addr) {
    sendto(sockfd, buffer, len, MSG_CONFIRM, (const struct sockaddr *) &addr, len);
}

Socket::~Socket() {

}


void Socket::parseHumanReadableIp() {

    /*
     * let's have some fun here and convert s_addr to a human readable ip
     * todo: optimize this away into diagnostics logging that can be toggled
     * on and off when an observer attaches to diagnostics port
     * 
     */

    char ip[12];
    memset(ip, 0, 12);

    strcpy(ip, (char*)inet_ntoa((struct in_addr)cliaddr.sin_addr));

    cout << "Socket: " << ip << ":" << cliaddr.sin_port << endl;
}


