#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <iterator>
#include <iostream>
#include <string.h>

#include "Platform.hpp"
#include "Socket.hpp"
#include "Enfora.hpp"

using namespace std;

void unitTestEnforaParsing();
void runUnitTests();

#define PI 3.14159
#define UDP_PORT 1721
#define MICROS_IN_MILLIS 1000
#define MILLIS_IN_SECONDS 1000

// #define ENFORA_EVT_TIMED		1
// #define ENFORA_EVT_DIST 		2
// #define ENFORA_EVT_OPTO1 		31
// #define ENFORA_EVT_PWRUP 		50

// #define ENFORA_MSG_SHORT	22
// #define ENFORA_MSG_LONG		51

//https://github.com/johncobb/sam4s_telit/


Socket server;

uint8_t msg_buffer[128] = {0};

/*
 header: 	4
 parm1:  	4
 mdmid:    	8
 rtc:		6

 */

/*
enfora standard message
len: 51
*/
typedef struct {
	uint32_t header;
	uint32_t evt_code;
	uint8_t modem_id[8];
	uint64_t rtc;
	uint8_t iocfg;
	uint8_t iogpio;
	uint8_t evt_cat;

	uint32_t gps_dte;
	uint8_t gps_sts;
	uint32_t gps_lat;
	uint32_t gps_lng;
	uint16_t gps_vel;
	uint16_t gps_hdg;
	uint32_t gps_tme;
	uint32_t gps_alt;
	uint8_t gps_sat;
	uint32_t gps_odm;
	
} enfora_msg_t;

/*
enfora powerup message
len: 22
*/
typedef struct {
	uint32_t header;
	uint32_t evt_code;
	uint8_t modem_id[8];
	uint64_t rtc;
	uint8_t iocfg;
	uint8_t iogpio;
	uint8_t evt_cat;
} enfora_msg_short_t;

void log_msg_buffer(uint8_t *data, uint8_t len) {

	printf("len: %d msg: ", len);

	for (int i=0; i<len; i++) {
		printf("%02x", data[i]);

		// only colon between bytes ... skip the last
		if (i<(len-1)) {
			printf(":");
		} 
	}
	printf("\r\n");

}

/*
 * https://github.com/johncobb/echobase_sam4e16c/blob/master/src/wan/wan.c
 * 
 */

void parse_msg_short(uint8_t *data, enfora_msg_t *msg) {

	if (msg->evt_code == ENFORA_EVT_PWRUP) {
		msg->rtc = (((unsigned long)data[16]) << 40) | (((unsigned long)data[17]) << 32) | (((unsigned long)data[18]) << 24) | (((unsigned long)data[19]) << 16) | (((unsigned long)data[20]) << 8) | (unsigned long)data[21];
	} else {
		msg->iocfg = (uint8_t) data[22];
		msg->iogpio = (uint8_t) data[23];
		msg->evt_cat = (uint8_t) data[24];
	}

}

void parse_msg_long(uint8_t *data, enfora_msg_t *msg) {
	
	msg->iocfg = (uint8_t) data[16];
	msg->iogpio = (uint8_t) data[17];
	msg->evt_cat = (uint8_t) data[18];
	msg->gps_dte = (((uint8_t)data[19]) << 16) | (((uint8_t)data[20]) << 8) | (uint8_t)data[21];
	msg->gps_sts = (uint8_t)data[22];
	msg->gps_lat = (((uint32_t)data[23]) << 16) | (((uint32_t)data[24]) << 8) | (uint32_t)data[25];
	msg->gps_lng = (((uint32_t)data[26]) << 24) | (((uint32_t)data[27]) << 16) | (((uint32_t)data[28]) << 8) | (uint32_t)data[29];
	msg->gps_vel = (((uint16_t)data[30]) << 8) | (uint16_t)data[31];
	msg->gps_hdg = (((uint16_t)data[32]) << 8) | (uint16_t)data[33];
	msg->gps_tme = (((uint32_t)data[34]) << 16) | (((uint32_t)data[35]) << 8) | (uint32_t)data[36];
	msg->gps_alt = (((uint32_t)data[37]) << 16) | (((uint32_t)data[38]) << 8) | (uint32_t)data[39];
	msg->gps_sat = (uint8_t)data[40];
	msg->gps_odm = (((uint32_t)data[41]) << 24) | (((uint32_t)data[42]) << 16) | (((uint32_t)data[43]) << 8) | (uint32_t)data[44];
	msg->rtc = (((unsigned long)data[45]) << 40) | (((unsigned long)data[46]) << 32) | (((unsigned long)data[47]) << 24) | (((unsigned long)data[48]) << 16) | (((unsigned long)data[49]) << 8) | (unsigned long)data[50];

}

// void parse_device_msg(uint8_t *data, enfora_msg_t *msg) {
// 	memcpy(msg, data, sizeof(enfora_msg_t));

// }

void parse_device_msg(uint8_t *data, enfora_msg_t *msg, long len) {

	log_msg_buffer(msg_buffer, len);

	msg->header = (((unsigned long)data[0]) << 24) | (((unsigned long)data[1]) << 16) | (((unsigned long)data[2]) << 8) | (unsigned long)data[3];
	msg->evt_code = (((unsigned long)data[4]) << 24) | (((unsigned long)data[5]) << 16) | (((unsigned long)data[6]) << 8) | (unsigned long)data[7];
	msg->modem_id[0] = data[8];
	msg->modem_id[1] = data[9];
	msg->modem_id[2] = data[10];
	msg->modem_id[3] = data[11];
	msg->modem_id[4] = data[12];
	msg->modem_id[5] = data[13];
	msg->modem_id[6] = data[14];
	msg->modem_id[7] = data[15];
	
	printf("msg->header: %u\r\n", msg->header);
	printf("msg->evt_code: %u\r\n", msg->evt_code);
	printf("msg->modem_id: %s\r\n", msg->modem_id);

	if (msg->evt_code == ENFORA_EVT_PWRUP) {
		cout << "POWERUP" << endl;
	} else if (msg->evt_code == ENFORA_EVT_OPTO1) {
		cout << "ENFORA_EVT_OPTO1" << endl;
	}
	// printf("msg->rtc: %llu\r\n", msg->rtc);	
	
	// spaghetti code for processing enfora messages
	try {
	
		if (len == ENFORA_MSG_SHORT) {
			parse_msg_short(msg_buffer, msg);
		} else if (len == ENFORA_MSG_LONG) {
			parse_msg_long(msg_buffer, msg);
		} else {
		
			throw "Invalid message length.";
		}
	} catch( const char* msg) {
		cout << "Exception occured: " << msg << endl;
	}

}

int main () {
	
	// runUnitTests();
	// return 0;

	enfora_msg_t enfora_msg;

	char buffer[BUFFER_SIZE] = {0};

	cout << "Platform: " << PLATFORM << endl;

	try {
		server = Socket(UDP_PORT);

		cout << "Socket listeneing on port: " << server.port << endl;
		cout << "Initialized: " << server.initialized << endl;
		cout << "Buffer size: " << sizeof(server.buffer) << endl;

		while(true) {

			long len = server.receive(msg_buffer, BUFFER_SIZE);
			if (len > 0) {
				// parse_device_msg(msg_buffer, &enfora_msg, len);
				Enfora msg = Enfora(msg_buffer, len);
				msg.parseMessage();
			}

			usleep(100*MICROS_IN_MILLIS); // 100 millis
		}

	} catch( const char* msg) {
		cout << "Exception occured: " << msg << endl;
		exit(EXIT_FAILURE); 
	}




	

	
        
}

void runUnitTests() {
	unitTestEnforaParsing();
}

void unitTestEnforaParsing() {
	uint8_t b[5] = {'H', 'e', 'l', 'l', 'o'};
	Enfora e = Enfora(b, 5);
	e.parsingTest();
}