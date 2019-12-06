/**
 * @file main.cpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <iterator>
#include <iostream>
#include <chrono>
#include <string.h>
#include <sys/time.h>
#include <vector>
#include <iomanip> //setprecision(n)


#include "Platform.hpp"
#include "Socket.hpp"
#include "MessageBase.hpp"
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
void runPerformanceTest();



static clock_t clock_time;
static clock_t perf_start;
static clock_t perf_end;

Socket server;
vector <MessageBase> connections;


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
	

	// runPerformanceTest();
	// return 0;

	char buffer[BUFFER_SIZE] = {0};

	cout << "Platform: " << PLATFORM << endl;
	cout << "Startup: " << clock() << endl;

	try {

		server = Socket(UDP_PORT);

		cout << "Socket listeneing on port: " << server.port << endl;
		cout << "Initialized: " << server.initialized << endl;
		cout << "Buffer size: " << sizeof(server.buffer) << endl;

		while(true) {

			long len = server.receive(msg_buffer, BUFFER_SIZE);
			// cout << "received len: " << len << endl;
			cout << "log clock: " << clock() << endl;
			if (len > 0) {
				//cout << "HERE IS THE LENGTH: " << len << endl;
				Enfora msg = Enfora(msg_buffer, len);
				msg.parseMessage();
				connections.push_back(msg);

				cout << "log connections: " << connections.size() << endl;
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
	gps.velocity = 100;
	gps.latitude = 37;
	gps.longitude = 87;

	gps.parsingTest();
}

void runPerformanceTest() {
	// https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
	perf_start = clock();
	for (int i=0; i<1000; i++) {
		int x = 0;
	}

	perf_end = clock();

	double time_taken = double(perf_end - perf_start) / double(CLOCKS_PER_SEC); 
    cout << "Time taken by program is : " << fixed  
         << time_taken << setprecision(5); 
    cout << " sec " << endl; 
}