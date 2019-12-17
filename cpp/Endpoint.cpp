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

vector <Endpoint*> Endpoint::endpoints;

Endpoint::Endpoint() {

}

Endpoint::Endpoint(uint8_t *data, unsigned long len):data(data), len(len) {

}

Endpoint::Endpoint(uint8_t *data, unsigned long len, endpoint_t *endpoint):data(data), len(len) {

	setEndpoint(endpoint);

}


Endpoint* Endpoint::createEndpoint(uint8_t *data, unsigned long len, endpoint_t *target) {

	/* try to identify endpoint */
    Endpoint *endpoint = identify(target);

	/* we found so return */
	if (endpoint != NULL) {
		return endpoint;
	} 

	/* no endpoint found so return a new one */
	endpoint = new Endpoint(data, len, target);

	/* add new endpoint to the vector for future reference */
	Endpoint::endpoints.push_back(endpoint);

	return endpoint;
}


/*
 * try to identify the incoming connection endpoint. if we have
 * a record of the endpoint update it otherwise we will create 
 * a new one.
 * 
 */
Endpoint* Endpoint::identify(endpoint_t *target) {

	Endpoint *ep = NULL;

	/* try to find the endpoint in the _endpoints vector */
	for (int i=0; i<Endpoint::endpoints.size(); i++) {
		ep = Endpoint::endpoints[i];

		/* if the device/message id matches the target endpoint device/message id
		 * we have a match.
		 */
		// if (ep->getEndpoint()->id == target->id) {
		// 	cout << "log found endpoint: " << ep->getEndpoint()->id << endl;
		// 	return ep;
		// }

		if (ep->clientId == target->id) {
			cout << "log found endpoint: " << ep->getEndpoint()->id << endl;
			return ep;
		}		
	}

	/* otherwise return a null pointer */
	return ep;
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

