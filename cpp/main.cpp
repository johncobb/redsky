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
#include <string.h>
#include <vector>
#include <iomanip> //setprecision(n)

#include "Platform.hpp"
#include "Socket.hpp"
#include "EndpointBase.hpp"
#include "Endpoint.hpp"
#include "Enfora.hpp"
#include "Gps.hpp"
#include "Message.hpp"

using namespace std;

#define PI 3.14159 /* pi always comes in handy */
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
void runChronoPerformanceTest();

void sendUdpResponse(endpoint_t sinfo);
int findClientByEndpoint(Endpoint endpoint);

static clock_t clock_time;
static clock_t perf_start;
static clock_t perf_end;

Socket server;
// vector <EndpointBase> connections;
// vector <Endpoint*> _endpoints;
vector <Message*> _messages;


/*
 * incoming device-messages may arrive on different ports each time the server
 * receives them. it is important to track the device-message by id and associate ip address and port
 * of message arrival. this allows us to manage the endpoint for each device-message in the event
 * the server needs to transmit a reply. this also allows the server to prune stale connections that
 * have exceeded the timeout threshold.
 * 
 */

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
			endpoint_t ep_info;

			long len = server.receiveFrom(msg_buffer, BUFFER_SIZE, &ep_info);
			
			/* create a new endpoint for referencing */
			Endpoint *ep = Endpoint::createEndpoint(msg_buffer, len, &ep_info);

			// cout << "received len: " << len << endl;
			cout << "log clock: " << clock() << endl;
			if (ep_info.len > 0) {

				/* try to parse the message, this method returns a pointer
				   to a new message of type parsed */
				Message *msg = Message::createMessage(msg_buffer, len, ep);

				/* if we successfully parsed add to vector */
				if (msg != NULL) {
					// ep->clientId = msg->id;
					_messages.push_back(msg);
				}

				/* log some interesting info :p */
				cout << "log endpoints: " << Endpoint::endpoints.size() << endl;
				cout << "log endpoint clientId: " << ep->clientId << endl;
				cout << "log endpoint time: " << ep->timestamp << endl;
				cout << "log message time: " << msg->timestamp << endl;
				
			}

			usleep(100*MICROS_IN_MILLIS); // 100 millis
		}

	} catch( const char* msg) {
		cout << "Exception occured: " << msg << endl;
		exit(EXIT_FAILURE); 
	}
 
}

void sendUdpResponse(endpoint_t sck_info) {
	string cmd_at = "AT$MSGSND=0,\"AT\0D\"";
	server.send(cmd_at.c_str(), cmd_at.size(), sck_info.addr);
}

void runUnitTests() {
	
	usleep(100); // let system breath or we will overwrite cout buffer
	unitTestGpsParsing();
	
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



// void runChronoPerformanceTest() {

// 	// using namespace std::literals::chrono_literals;
// 	auto perf_start = std::chrono::high_resolution_clock::now();

// 	for (int i=0; i<1000; i++) {
// 		int x = 0;
// 	}

// 	auto perf_end = std::chrono::high_resolution_clock::now();

// 	std::chrono::duration<float> lapse = perf_end - perf_start;
// 	cout << "chrono duration: " << lapse.count() << "s " << endl;
// }