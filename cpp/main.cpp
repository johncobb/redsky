#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <iterator>
#include <iostream>
#include <string.h>

#include "Platform.hpp"
#include "Socket.hpp"
using namespace std;

#define PI 3.14159
#define UDP_PORT 1721
#define MICROS_IN_MILLIS 1000
#define MILLIS_IN_SECONDS 1000


//https://github.com/johncobb/sam4s_telit/


Socket server;

uint8_t msg_buffer[128] = {0};

typedef struct {
	uint8_t hdr;
	uint8_t type;
	uint8_t id;
} enfora_msg_t;

void log_msg_buffer(uint8_t *data, uint8_t len) {

	printf("msg: ");

	for (int i=0; i<len; i++) {
		printf("%02x", data[i]);

		// only colon between bytes ... skip the last
		if (i<(len-1)) {
			printf(":");
		} 
	}
	printf("\r\n");

}

void parse_device_msg(uint8_t *data, enfora_msg_t *msg) {
	memcpy(msg, data, sizeof(enfora_msg_t));
}

int main () {
	
	enfora_msg_t enfora_msg;

	char buffer[MAXLINE] = {0};

	cout << "Platform: " << PLATFORM << endl;

	
	try {
		server = Socket(UDP_PORT);

		cout << "Socket listeneing on port: " << server.port << endl;
		cout << "Initialized: " << server.initialized << endl;
		cout << "Buffer size: " << sizeof(server.buffer) << endl;

		while(true) {

			int len = server.receive_ex(msg_buffer, 128);
			parse_device_msg(msg_buffer, &enfora_msg);

			if (len > 0) {
				log_msg_buffer(msg_buffer, len);
			}

			usleep(100*MICROS_IN_MILLIS); // 100 millis
		}

	} catch( const char* msg) {
		cout << "Exception occured: " << msg << endl;
		exit(EXIT_FAILURE); 
	}

	

	
        
}
