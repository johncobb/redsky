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
#include "EndpointBase.hpp"
#include "Endpoint.hpp"
#include "Gps.hpp"

using namespace std;

#define PI 3.14159
#define UDP_PORT 1721
#define MICROS_IN_MILLIS 1000
#define MILLIS_IN_SECONDS 1000

/*
 * Unit test scaffolding
 */
void unitTestEndpointParsing();
void unitTestGpsParsing();
void runUnitTests();
void runPerformanceTest();

void sendUdpResponse(endpoint_t sinfo);

static clock_t clock_time;
static clock_t perf_start;
static clock_t perf_end;

Socket server;
vector <EndpointBase> connections;


uint8_t msg_buffer[128] = {0};

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
			endpoint_t sck_info;

			long len = server.receiveFrom(msg_buffer, BUFFER_SIZE, &sck_info);
			
			// cout << "received len: " << len << endl;
			cout << "log clock: " << clock() << endl;
			if (sck_info.len > 0) {

				Endpoint msg = Endpoint(msg_buffer, len, &sck_info);
				
				msg.parseMessage();
				connections.push_back(msg);
				cout << "log sck id: " << msg.getEndpoint()->id << endl;

				cout << "log connections: " << connections.size() << endl;
				// sendUdpResponse(sinfo);
			}

			usleep(100*MICROS_IN_MILLIS); // 100 millis
		}

	} catch( const char* msg) {
		cout << "Exception occured: " << msg << endl;
		exit(EXIT_FAILURE); 
	}
 
}

int findClientByEndpoint(sockaddr_in endpoint) {

	
	// for (auto &m : connections) {
	// 	if (m.getEndpoint()->len == 0) {
	// 		cout << "we found the connection" << endl;
	// 	}
	// }

	for (int i=0; i<connections.size(); i++) {
		EndpointBase msg = connections[i];
		cout << msg.getEndpoint()->id << endl;
		return i;
	}

	return -1;
	
	
}

void sendUdpResponse(endpoint_t sck_info) {
	string cmd_at = "AT$MSGSND=0,\"AT\0D\"";
	server.send(cmd_at.c_str(), cmd_at.size(), sck_info.addr);
}

void runUnitTests() {
	
	unitTestEndpointParsing();
	usleep(100); // let system breath or we will overwrite cout buffer
	unitTestGpsParsing();
	
}

void unitTestEndpointParsing() {
	uint8_t b[5] = {'H', 'e', 'l', 'l', 'o'};
	Endpoint e = Endpoint(b, 5);
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