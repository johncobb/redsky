/**
 * @file Gps.cpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#include <iostream>
#include "Gps.hpp"

using namespace std;

Gps::Gps() {

}

Gps::Gps(uint8_t *data, int len):data(data), len(len) {

}

void Gps::parse() {
    parse(data, len);
}
void Gps::parse(uint8_t *data, int len) {
	
    logMessageBuffer(data, len);
}

void Gps::logMessageBuffer(uint8_t *data, long len) {

	printf("len: %ld msg: ", len);

	for (int i=0; i<len; i++) {
		printf("%02x", data[i]);

		// only colon between bytes ... skip the last
		if (i<(len-1)) {
			printf(":");
		} 
	}
	printf("\r\n");

}

void Gps::parsingTest() {
	// logMessageBuffer(data, len);

    cout << "Gps::parse(data: " << data << " len: " << len << ")" << endl;
	cout << "GPS::m_Position: lat: " << latitude
									 << " lng: " << longitude
									 << " vel: " << velocity 
									 << endl;
}

Gps::~Gps() {

}