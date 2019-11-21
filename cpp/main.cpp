#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <iterator>
#include <iostream>

#include "Socket.h"
using namespace std;

#define PI 3.14159

#define AREA_CIRCLE(radius) (PI*(radius*radius))

int main () {

	Socket socket = Socket();
	socket.setEndpointAddress("http://localhost");
	cout << "Socket endpoint address: " << socket.getEndpointAddress() << endl;

}
