/**
 * @file MessageFactory.cpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#include <iostream>
#include "MessageFactory.hpp"


using namespace std;

MessageFactory::MessageFactory() {

}

/*
 * Identify message based on port number
 * 
 */
MessageFactory::MessageType MessageFactory::identify(Endpoint *ep) {

	if (ep->port == 1721) {
		return TypeEnfora;
	}


	return TypeUnknown;
}

/*
 * Identify message based on data received
 * 
 */
MessageFactory::MessageType MessageFactory::identify(uint8_t *data, unsigned long len) {


	if (len >= 4) {
		if (data[0] == 0x00 && data[1] == 0x05 && data[2] == 0x02 && data[3] == 0x00) {
			return TypeEnfora;
		}
	}

	return TypeUnknown;

}

MessageFactory::MessageType MessageFactory::identify(int type) {
	return (MessageFactory::MessageType) type;
}

MessageFactory::~MessageFactory() {

}