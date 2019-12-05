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
#include "Gps.hpp"

using namespace std;

#define PI 3.14159
#define UDP_PORT 1721
#define MICROS_IN_MILLIS 1000
#define MILLIS_IN_SECONDS 1000

/*
 * Unit test scaffolding
 */
void unitTestEnforaParsing();
void unitTestGpsParsing();
void runUnitTests();



Socket server;

uint8_t msg_buffer[128] = {0};

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


int main () {
	
	// runUnitTests();
	// return 0;

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
				//cout << "HERE IS THE LENGTH: " << len << endl;
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
	usleep(100); // let system breath or we will overwrite cout buffer
	unitTestGpsParsing();
	
}

void unitTestEnforaParsing() {
	uint8_t b[5] = {'H', 'e', 'l', 'l', 'o'};
	Enfora e = Enfora(b, 5);
	e.parsingTest();
}

void unitTestGpsParsing() {
	uint8_t x[5] = {'G', 'P', 'R', 'M', 'C'};
	Gps gps = Gps(x, 5);
	gps.m_Position.velocity = 100;
	gps.m_Position.latitude = 37;
	gps.m_Position.longitude = 87;

	gps.parsingTest();
}