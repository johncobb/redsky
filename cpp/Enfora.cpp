/**
 * @file Enfora.cpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#include <iostream>
#include "Enfora.hpp"

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

Enfora::Enfora() {
    gps = Gps();
}


Enfora::Enfora(uint8_t *data, unsigned long len):data(data), len(len) {
	/* parse the message identify encoded in the payload.
	   this will be used to identify the message as well as the 
	   endpoint from which the message arrived. */
	identify(data, len);

	/* parse data from message */
	parse(data, len);
}


uint64_t Enfora::identify(uint8_t *data, unsigned long len) {

    // we need at least 16 bytes to process the identifier of
    // an enfora message

	if (len >16) {

		id = (((uint64_t)data[8]) << 56) | 
						(((uint64_t)data[9]) << 48) | 
						(((uint64_t)data[10]) << 40) | 
						(((uint64_t)data[11]) << 32) | 
						(((uint64_t)data[12]) << 24) | 
						(((uint64_t)data[13]) << 16) | 
						(((uint64_t)data[14]) << 8) | 
						(uint64_t)data[15];
		return id;
	} else {
		return 0;
	}
}

void Enfora::parse(uint8_t *data, unsigned long len) {
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
	
	cout << "log queue_complete: " << queue_complete << endl;
	printf("log msg-header: %u\r\n", header);
	printf("log msg-type: %u\r\n", event_type);
	printf("log modem-id: %s\r\n", modem_id);

	if (event_type == ENFORA_EVT_PWRUP) {
		cout << "log evt: POWERUP" << endl;
	} else if (event_type == ENFORA_EVT_OPTO1) {
		cout << "log evt: ENFORA_EVT_OPTO1" << endl;
	} else {
		cout << "log evt: OTHER" << endl;
	}
	// printf("msg->realTimeClock: %llu\r\n", msg->realTimeClock);	
	
	// spaghetti code for processing Endpoint messages
	try {
	
		if (len == ENFORA_MSG_SHORT) {
			parseMessageShort(data);
		} else if (len == ENFORA_MSG_LONG) {
			parseMessageLong(data);
		} else {
		
			throw "Invalid message length.";
		}
	} catch( const char* msg) {
		cout << "Exception occured: " << msg << endl;
	}
}

void Enfora::parseMessageShort(uint8_t *data) {

	if (event_type == ENFORA_EVT_PWRUP) {
		rtc = (((unsigned long)data[16]) << 40) | (((unsigned long)data[17]) << 32) | (((unsigned long)data[18]) << 24) | (((unsigned long)data[19]) << 16) | (((unsigned long)data[20]) << 8) | (unsigned long)data[21];
	} else {
		iocfg = (uint8_t) data[22];
		iogpio = (uint8_t) data[23];
		event_cat = (uint8_t) data[24];
	}

}

void Enfora::parseMessageLong(uint8_t *data) {
	
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

void Enfora::logMessageBuffer(uint8_t *data, unsigned long len) {

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

void Enfora::parsingTest() {
    cout << "Endpoint::parse(data: " << data << " len: " << len << ")" << endl;
}


Enfora::~Enfora() {
	cout << "Enfora::~Enfora" << endl;
}