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



//https://github.com/johncobb/sam4s_telit/


Socket server;


int main () {
	
	char buffer[MAXLINE] = {0};

	cout << "Platform: " << PLATFORM << endl;


	try {
		server = Socket(UDP_PORT);

		cout << "Socket listeneing on port: " << server.port << endl;
		cout << "Initialized: " << server.initialized << endl;
		cout << "Buffer size: " << sizeof(server.buffer) << endl;

		while(true) {
			memset(buffer, '\0', MAXLINE);
			int len = server.receive(buffer, MAXLINE);

		}

	} catch( const char* msg) {
		cout << "Exception occured: " << msg << endl;
		exit(EXIT_FAILURE); 
	}

	
	
        
}
