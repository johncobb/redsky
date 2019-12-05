/**
 * @file Gps.hpp
 *
 * @brief This message displayed in Doxygen Files index
 *
 * @ingroup PackageName
 * (Note: this needs exactly one @defgroup somewhere)
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Tweet: @johncobbtweets
 *
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

		typedef struct {
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

		} position_t;

		position_t m_Position;

		virtual ~Gps();

	private:
		
		void logMessageBuffer(uint8_t *data, long len);

		double myPrivateMethod() {
			return 1.0;
		}
};

#endif