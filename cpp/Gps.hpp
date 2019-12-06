/**
 * @file Gps.hpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#ifndef GPS_H
#define GPS_H

#include <stdint.h> 

using namespace std;

class Gps {
	public:
		Gps();
		Gps(uint8_t *data, int len);

        bool initialized;
		uint8_t *data;
		int len;
		void parse();
		void parse(uint8_t *data, int len);
		void parsingTest();


		uint32_t date;
		uint8_t status;
		uint32_t longitude;
		uint32_t latitude;
		uint16_t velocity;
		uint16_t heading;
		uint32_t time;
		uint32_t altitude;
		uint8_t satellites;
		uint32_t odometer;


		virtual ~Gps();

	private:
		
		void logMessageBuffer(uint8_t *data, long len);

		double myPrivateMethod() {
			return 1.0;
		}
};

#endif