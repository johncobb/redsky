#include "Enfora.hpp"
// #include "Gps.hpp"
#include <iostream>


using namespace std;


/*
 * https://github.com/johncobb/sam4s_telit/
 * https://github.com/johncobb/echobase_sam4e16c/blob/master/src/wan/wan.c
 * 
 * enfora standard message
 * len: 51
 * 
 * enfora powerup message
 * len: 22
 * 
 * header: 	4
 * parm1: 	4
 * mdmid: 	8
 * rtc:		6
 * 
*/

Enfora::Enfora() {
	m_Gps = Gps();
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

	m_Header = (((unsigned long)data[0]) << 24) | (((unsigned long)data[1]) << 16) | (((unsigned long)data[2]) << 8) | (unsigned long)data[3];
	m_EventType = (((unsigned long)data[4]) << 24) | (((unsigned long)data[5]) << 16) | (((unsigned long)data[6]) << 8) | (unsigned long)data[7];
	m_ModemId[0] = data[8];
	m_ModemId[1] = data[9];
	m_ModemId[2] = data[10];
	m_ModemId[3] = data[11];
	m_ModemId[4] = data[12];
	m_ModemId[5] = data[13];
	m_ModemId[6] = data[14];
	m_ModemId[7] = data[15];
	
	printf("msg->m_Header: %u\r\n", m_Header);
	printf("msg->m_EventType: %u\r\n", m_EventType);
	printf("msg->m_ModemId: %s\r\n", m_ModemId);

	if (m_EventType == ENFORA_EVT_PWRUP) {
		cout << "POWERUP" << endl;
	} else if (m_EventType == ENFORA_EVT_OPTO1) {
		cout << "ENFORA_EVT_OPTO1" << endl;
	}
	// printf("msg->m_RTC: %llu\r\n", msg->m_RTC);	
	
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

	if (m_EventType == ENFORA_EVT_PWRUP) {
		m_RTC = (((unsigned long)data[16]) << 40) | (((unsigned long)data[17]) << 32) | (((unsigned long)data[18]) << 24) | (((unsigned long)data[19]) << 16) | (((unsigned long)data[20]) << 8) | (unsigned long)data[21];
	} else {
		m_IOCFG = (uint8_t) data[22];
		m_IOGPIO = (uint8_t) data[23];
		m_EventCategory = (uint8_t) data[24];
	}

}

void Enfora::parseMessageLong(uint8_t *data) {
	
	m_IOCFG = (uint8_t) data[16];
	m_IOGPIO = (uint8_t) data[17];
	m_EventCategory = (uint8_t) data[18];
	m_Gps.m_Position.date = (((uint8_t)data[19]) << 16) | (((uint8_t)data[20]) << 8) | (uint8_t)data[21];
	m_Gps.m_Position.status = (uint8_t)data[22];
	m_Gps.m_Position.latitude = (((uint32_t)data[23]) << 16) | (((uint32_t)data[24]) << 8) | (uint32_t)data[25];
	m_Gps.m_Position.longitude = (((uint32_t)data[26]) << 24) | (((uint32_t)data[27]) << 16) | (((uint32_t)data[28]) << 8) | (uint32_t)data[29];
	m_Gps.m_Position.velocity = (((uint16_t)data[30]) << 8) | (uint16_t)data[31];
	m_Gps.m_Position.heading = (((uint16_t)data[32]) << 8) | (uint16_t)data[33];
	m_Gps.m_Position.time = (((uint32_t)data[34]) << 16) | (((uint32_t)data[35]) << 8) | (uint32_t)data[36];
	m_Gps.m_Position.altitude = (((uint32_t)data[37]) << 16) | (((uint32_t)data[38]) << 8) | (uint32_t)data[39];
	m_Gps.m_Position.satellites = (uint8_t)data[40];
	m_Gps.m_Position.odometer = (((uint32_t)data[41]) << 24) | (((uint32_t)data[42]) << 16) | (((uint32_t)data[43]) << 8) | (uint32_t)data[44];
	m_RTC = (((unsigned long)data[45]) << 40) | (((unsigned long)data[46]) << 32) | (((unsigned long)data[47]) << 24) | (((unsigned long)data[48]) << 16) | (((unsigned long)data[49]) << 8) | (unsigned long)data[50];

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

