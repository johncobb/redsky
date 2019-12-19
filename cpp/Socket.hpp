/**
 * @file Socket.hpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

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
#include <stdint.h> 
#include <netdb.h>

using namespace std;

#define PORT 8080
#define BUFFER_SIZE 128

// https://adaickalavan.github.io/programming/udp-socket-programming-in-cpp-and-python/
typedef struct {
	uint64_t id;
	sockaddr_in addr;
	long len;
	clock_t timestamp;
} endpoint_t;


class Socket {
	public:
		Socket();
		Socket(uint16_t port);
		
		virtual ~Socket();
		
		int sockfd;
		uint8_t buffer[BUFFER_SIZE];
		bool initialized;
		uint8_t socketFamily;
		uint16_t inAddr;
		uint16_t port;
		struct sockaddr_in servaddr;
		struct sockaddr_in cliaddr;
		long receiveFrom(uint8_t *buffer, int max);
		long receiveFrom(uint8_t *buffer, int max, endpoint_t *info);
		long receiveFromSelect(uint8_t *buffer, int max, endpoint_t *info);

		/* select api members */
		fd_set master;
		void enableSelect();

		// TODO: New code
		// sockaddr_in receiveFrom(uint8_t* buffer, int len, int flags);

		void send(const char* buffer, int len, sockaddr_in addr);
	private:
		long send(char *msg);
		void parseHumanReadableIp();
		
		double myPrivateMethod() {
			return 1.0;
		}
};

#endif
