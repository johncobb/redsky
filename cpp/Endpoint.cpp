/**
 * @file Endpoint.cpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#include "Endpoint.hpp"
// #include "Gps.hpp"
#include <iostream>


using namespace std;


/*
 * 
 * 
 * 
 * https://github.com/johncobb/echobase_sam4e16c/blob/master/src/wan/wan.c
 * 
 * Endpoint standard message
 * len: 51
 * 
 * Endpoint powerup message
 * len: 22
 * 
 * header: 	4
 * parm1: 	4
 * mdmid: 	8
 * rtc:		6
 * 
*/

Endpoint::Endpoint() {
	gps = Gps();
}

Endpoint::Endpoint(uint8_t *data, unsigned long len):data(data), len(len) {

}

Endpoint::Endpoint(uint8_t *data, unsigned long len, endpoint_t *endpoint):data(data), len(len) {
	// endpoint = endpoint;
	setEndpoint(endpoint);
	parseEndpointId();
}

uint64_t Endpoint::parseEndpointId() {

	if (endpoint->len >16) {
		endpoint->id = (((uint64_t)data[8]) << 56) | 
						(((uint64_t)data[9]) << 48) | 
						(((uint64_t)data[10]) << 40) | 
						(((uint64_t)data[11]) << 32) | 
						(((uint64_t)data[12]) << 24) | 
						(((uint64_t)data[13]) << 16) | 
						(((uint64_t)data[14]) << 8) | 
						(uint64_t)data[15];
		return endpoint->id;
	} else {
		return 0;
	}
}



void Endpoint::parse() {
    cout << "Endpoint::parse()" << endl;
}

void Endpoint::parseMessage() {

	char ip[12];
	memset(ip, 0, 12);

	strcpy(ip, (char*)inet_ntoa((struct in_addr)getEndpoint()->addr.sin_addr));

	cout << "log client addr: " << ip << ":" << getEndpoint()->addr.sin_port << endl;

    parseMessage(data);
}

void Endpoint::parseMessage(uint8_t *data) {
    logMessageBuffer(data, len);

	header = (((unsigned long)data[0]) << 24) | (((unsigned long)data[1]) << 16) | (((unsigned long)data[2]) << 8) | (unsigned long)data[3];
	event_type = (((unsigned long)data[4]) << 24) | (((unsigned long)data[5]) << 16) | (((unsigned long)data[6]) << 8) | (unsigned long)data[7];
	modem_id[0] = data[8];
	modem_id[1] = data[9];
	modem_id[2] = data[10];
	modem_id[3] = data[11];
	modem_id[4] = data[12];
	modem_id[5] = data[13];
	modem_id[6] = data[14];
	modem_id[7] = data[15];
	
	printf("log msg-header: %u\r\n", header);
	printf("log msg-type: %u\r\n", event_type);
	printf("log modem-id: %s\r\n", modem_id);

	if (event_type == Endpoint_EVT_PWRUP) {
		cout << "log evt: POWERUP" << endl;
	} else if (event_type == Endpoint_EVT_OPTO1) {
		cout << "log evt: Endpoint_EVT_OPTO1" << endl;
	} else {
		cout << "log evt: OTHER" << endl;
	}
	// printf("msg->realTimeClock: %llu\r\n", msg->realTimeClock);	
	
	// spaghetti code for processing Endpoint messages
	try {
	
		if (len == Endpoint_MSG_SHORT) {
			parseMessageShort(data);
		} else if (len == Endpoint_MSG_LONG) {
			parseMessageLong(data);
		} else {
		
			throw "Invalid message length.";
		}
	} catch( const char* msg) {
		cout << "Exception occured: " << msg << endl;
	}
}

void Endpoint::parseMessageShort(uint8_t *data) {

	if (event_type == Endpoint_EVT_PWRUP) {
		rtc = (((unsigned long)data[16]) << 40) | (((unsigned long)data[17]) << 32) | (((unsigned long)data[18]) << 24) | (((unsigned long)data[19]) << 16) | (((unsigned long)data[20]) << 8) | (unsigned long)data[21];
	} else {
		iocfg = (uint8_t) data[22];
		iogpio = (uint8_t) data[23];
		event_cat = (uint8_t) data[24];
	}

}

void Endpoint::parseMessageLong(uint8_t *data) {
	
	iocfg = (uint8_t) data[16];
	iogpio = (uint8_t) data[17];
	event_cat = (uint8_t) data[18];
	gps.date = (((uint8_t)data[19]) << 16) | (((uint8_t)data[20]) << 8) | (uint8_t)data[21];
	gps.status = (uint8_t)data[22];
	gps.latitude = (((uint32_t)data[23]) << 16) | (((uint32_t)data[24]) << 8) | (uint32_t)data[25];
	gps.longitude = (((uint32_t)data[26]) << 24) | (((uint32_t)data[27]) << 16) | (((uint32_t)data[28]) << 8) | (uint32_t)data[29];
	gps.velocity = (((uint16_t)data[30]) << 8) | (uint16_t)data[31];
	gps.heading = (((uint16_t)data[32]) << 8) | (uint16_t)data[33];
	gps.time = (((uint32_t)data[34]) << 16) | (((uint32_t)data[35]) << 8) | (uint32_t)data[36];
	gps.altitude = (((uint32_t)data[37]) << 16) | (((uint32_t)data[38]) << 8) | (uint32_t)data[39];
	gps.satellites = (uint8_t)data[40];
	// odometer is calculated and stored locally on the device and is not a part of the GPRMC specification
	odometer = (((uint32_t)data[41]) << 24) | (((uint32_t)data[42]) << 16) | (((uint32_t)data[43]) << 8) | (uint32_t)data[44];
	rtc = (((unsigned long)data[45]) << 40) | (((unsigned long)data[46]) << 32) | (((unsigned long)data[47]) << 24) | (((unsigned long)data[48]) << 16) | (((unsigned long)data[49]) << 8) | (unsigned long)data[50];

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

void Endpoint::parsingTest() {
    cout << "Endpoint::parse(data: " << data << " len: " << len << ")" << endl;
}

Endpoint::~Endpoint() {

}

