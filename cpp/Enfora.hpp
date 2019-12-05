#ifndef ENFORA_H
#define ENFORA_H

#include <stdint.h> 
#include "Gps.hpp"
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
		Gps m_Gps;

		uint32_t m_Header;
		uint32_t m_EventType;
		uint8_t m_ModemId[8];
		uint64_t m_RTC;
		uint8_t m_IOCFG;
		uint8_t m_IOGPIO;
		uint8_t m_EventCategory;
		uint32_t m_NotifyType;

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
