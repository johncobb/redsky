#ifndef ENFORA_H
#define ENFORA_H

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

using namespace std;

#define ENFORA_EVT_TIMED		1
#define ENFORA_EVT_DIST 		2
#define ENFORA_EVT_OPTO1 		31
#define ENFORA_EVT_PWRUP 		50

#define ENFORA_MSG_SHORT	22
#define ENFORA_MSG_LONG		51

/*
enfora standard message
len: 51
*/

class Enfora {
	public:
		Enfora();
		Enfora(uint8_t *data, int len);

		virtual ~Enfora();
        uint8_t *data;
		int len;
		bool initialized;

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
		
		void parseMessage();
		void parseMessage(uint8_t *data);
        void parse();
		void parsingTest();


	
	private:

		void parseMessageShort(uint8_t *data);
		void parseMessageLong(uint8_t *data);
		void logMessageBuffer(uint8_t *data, long len);
		

		double myPrivateMethod() {
			return 1.0;
		}
	
	

};

#endif
