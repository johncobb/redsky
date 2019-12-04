#include "Enfora.hpp"
#include <iostream>

using namespace std;


Enfora::Enfora() {

}

Enfora::Enfora(uint8_t *data, int len):data(data), len(len) {

}


void Enfora::parse() {
    cout << "Enfora::parse()" << endl;
}

void Enfora::parseMessage() {
    parseMessage(data);
}
void Enfora::parseMessage(uint8_t *data) {
    logMessageBuffer(data, len);

	header = (((unsigned long)data[0]) << 24) | (((unsigned long)data[1]) << 16) | (((unsigned long)data[2]) << 8) | (unsigned long)data[3];
	evt_code = (((unsigned long)data[4]) << 24) | (((unsigned long)data[5]) << 16) | (((unsigned long)data[6]) << 8) | (unsigned long)data[7];
	modem_id[0] = data[8];
	modem_id[1] = data[9];
	modem_id[2] = data[10];
	modem_id[3] = data[11];
	modem_id[4] = data[12];
	modem_id[5] = data[13];
	modem_id[6] = data[14];
	modem_id[7] = data[15];
	
	printf("msg->header: %u\r\n", header);
	printf("msg->evt_code: %u\r\n", evt_code);
	printf("msg->modem_id: %s\r\n", modem_id);

	if (evt_code == ENFORA_EVT_PWRUP) {
		cout << "POWERUP" << endl;
	} else if (evt_code == ENFORA_EVT_OPTO1) {
		cout << "ENFORA_EVT_OPTO1" << endl;
	}
	// printf("msg->rtc: %llu\r\n", msg->rtc);	
	
	// spaghetti code for processing enfora messages
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

	if (evt_code == ENFORA_EVT_PWRUP) {
		rtc = (((unsigned long)data[16]) << 40) | (((unsigned long)data[17]) << 32) | (((unsigned long)data[18]) << 24) | (((unsigned long)data[19]) << 16) | (((unsigned long)data[20]) << 8) | (unsigned long)data[21];
	} else {
		iocfg = (uint8_t) data[22];
		iogpio = (uint8_t) data[23];
		evt_cat = (uint8_t) data[24];
	}

}

void Enfora::parseMessageLong(uint8_t *data) {
	
	iocfg = (uint8_t) data[16];
	iogpio = (uint8_t) data[17];
	evt_cat = (uint8_t) data[18];
	gps_dte = (((uint8_t)data[19]) << 16) | (((uint8_t)data[20]) << 8) | (uint8_t)data[21];
	gps_sts = (uint8_t)data[22];
	gps_lat = (((uint32_t)data[23]) << 16) | (((uint32_t)data[24]) << 8) | (uint32_t)data[25];
	gps_lng = (((uint32_t)data[26]) << 24) | (((uint32_t)data[27]) << 16) | (((uint32_t)data[28]) << 8) | (uint32_t)data[29];
	gps_vel = (((uint16_t)data[30]) << 8) | (uint16_t)data[31];
	gps_hdg = (((uint16_t)data[32]) << 8) | (uint16_t)data[33];
	gps_tme = (((uint32_t)data[34]) << 16) | (((uint32_t)data[35]) << 8) | (uint32_t)data[36];
	gps_alt = (((uint32_t)data[37]) << 16) | (((uint32_t)data[38]) << 8) | (uint32_t)data[39];
	gps_sat = (uint8_t)data[40];
	gps_odm = (((uint32_t)data[41]) << 24) | (((uint32_t)data[42]) << 16) | (((uint32_t)data[43]) << 8) | (uint32_t)data[44];
	rtc = (((unsigned long)data[45]) << 40) | (((unsigned long)data[46]) << 32) | (((unsigned long)data[47]) << 24) | (((unsigned long)data[48]) << 16) | (((unsigned long)data[49]) << 8) | (unsigned long)data[50];

}

void Enfora::logMessageBuffer(uint8_t *data, long len) {

	printf("len: %ld msg: ", len);

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
    cout << "Enfora::parse(data: " << data << " len: " << len << ")" << endl;
}

Enfora::~Enfora() {

}

