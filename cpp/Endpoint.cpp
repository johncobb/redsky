/**
 * @file Endpoint.cpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#include <iostream>
#include "Endpoint.hpp"



using namespace std;

Endpoint::Endpoint() {

}

Endpoint::Endpoint(uint8_t *data, unsigned long len):data(data), len(len) {

}

Endpoint::Endpoint(uint8_t *data, unsigned long len, endpoint_t *endpoint):data(data), len(len) {

	setEndpoint(endpoint);

}


void Endpoint::logMessageBuffer(uint8_t *data, unsigned long len) {

	printf("log len: %ld msg: ", len);

	for (int i=0; i<len; i++) {
		printf("%02x", data[i]);

		// only colon between bytes ... skip the last
		if (i<(len-1)) {
			printf(":");
		} 
	}
	printf("\r\n");

}

Endpoint::~Endpoint() {

}

