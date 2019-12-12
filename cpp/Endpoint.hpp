/**
 * @file Endpoint.hpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <stdint.h> 
#include "EndpointBase.hpp"
#include "Gps.hpp"
using namespace std;

#define ENDPOINT_EVT_TIMED		1
#define ENDPOINT_EVT_DIST 		2
#define ENDPOINT_EVT_OPTO1 		31
#define ENDPOINT_EVT_PWRUP 		50

#define ENDPOINT_MSG_SHORT	22
#define ENDPOINT_MSG_LONG		51

/*
Endpoint standard message
len: 51
*/

class Endpoint : public EndpointBase {
	public:
		Endpoint();
		Endpoint(uint8_t *data, unsigned long len);
		Endpoint(uint8_t *data, unsigned long len, int x);
		Endpoint(uint8_t *data, unsigned long len, endpoint_t *endpoint);
		// todo: the following constructor is ability to track message by ip and port
		// allowing us to prune old/stale connections and maintain an updated list
		// of connections
		// Endpoint(uint8_t *data, unsigned long len, uint16_t addr, uint16_t port);

		virtual ~Endpoint();
        uint8_t *data;
		unsigned long len;
		uint16_t addr;
		uint16_t port;
		bool initialized;
		Gps gps;

		uint32_t header;
		uint32_t event_type;
		uint8_t modem_id[8];
		uint64_t rtc;
		uint8_t iocfg;
		uint8_t iogpio;
		uint8_t event_cat;
		uint32_t odometer;
		// uint32_t notifyType; // not yet implemented (tbd)

		uint64_t parseEndpointId();
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
