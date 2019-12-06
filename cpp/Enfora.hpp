/**
 * @file Enfora.hpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#ifndef ENFORA_H
#define ENFORA_H

#include <stdint.h> 
#include "MessageBase.hpp"
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

class Enfora : public MessageBase {
	public:
		Enfora();
		Enfora(uint8_t *data, unsigned long len);
		// todo: the following constructor is ability to track message by ip and port
		// allowing us to prune old/stale connections and maintain an updated list
		// of connections
		// Enfora(uint8_t *data, unsigned long len, uint16_t addr, uint16_t port);

		virtual ~Enfora();
        uint8_t *data;
		unsigned long len;
		uint16_t addr;
		uint16_t port;
		bool initialized;
		Gps gps;

		uint32_t header;
		uint32_t eventType;
		uint8_t modemId[8];
		uint64_t realTimeClock;
		uint8_t iocfg;
		uint8_t iogpio;
		uint8_t eventCategory;
		uint32_t odometer;
		// uint32_t notifyType; // not yet implemented (tbd)

		void parseMessage();
		void parseMessage(uint8_t *data);
        void parse();
		void parsingTest();

		// double myPublicMethod() {
		// 	return 3.0;
		// }

	private:

		void parseMessageShort(uint8_t *data);
		void parseMessageLong(uint8_t *data);
		void logMessageBuffer(uint8_t *data, unsigned long len);
		
		double myPrivateMethod() {
			return 1.0;
		}
	
	

};

#endif
