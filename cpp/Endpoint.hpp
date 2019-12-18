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
#include <vector>
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
		uint64_t clientId;

		sockaddr_in clientAddr;

		clock_t timestamp;

		static vector <Endpoint*> endpoints;
		static Endpoint *createEndpoint(uint8_t *data, unsigned long len, endpoint_t *target);

		static Endpoint *identify(endpoint_t *target);

		// double myPublicMethod() {
		// 	return 3.0;
		// }
	protected:
		
	

	private:

		void logMessageBuffer(uint8_t *data, unsigned long len);
		
		double myPrivateMethod() {
			return 1.0;
		}
	
	

};

#endif
