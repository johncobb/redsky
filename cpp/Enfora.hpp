/**
 * @file Enfora.hpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#ifndef ENFORA_H
#define ENFORA_H

#include <stdint.h> 
#include "Socket.hpp"
#include "Message.hpp"
#include "Gps.hpp"

using namespace std;

#define ENFORA_EVT_TIMED		1
#define ENFORA_EVT_DIST 		2
#define ENFORA_EVT_OPTO1 		31
#define ENFORA_EVT_PWRUP 		50

#define ENFORA_MSG_SHORT	22
#define ENFORA_MSG_LONG		51

#define ENFORA_ATMSGSEND = "AT$MSGSND=\"{0}\"\0D\r";


class Enfora : public Message {

    public:

        Enfora();
        Enfora(uint8_t *data, unsigned long len);
        
        virtual ~Enfora();

        uint8_t *data; // data buffer returned from socket
        unsigned long len; // data buffer length
        uint8_t ver; // message version
        // uint64_t id; // message identifier
        
        Gps gps;
        uint32_t header;
        uint32_t event_type;
        uint8_t modem_id[8];
        uint64_t rtc;
        uint8_t iocfg;
        uint8_t iogpio;
        uint8_t event_cat;
        uint32_t odometer;

        uint64_t identify(uint8_t *data, unsigned long len);
        void parse(uint8_t *data, unsigned long len);
        
        void parsingTest();
        /* template method */
        double myPublicMethod() {
          return 2.0;
        }

    protected:
      /* template method */
      double myProtectedMethod() {
        return 3.0;
      }

    private:

      void parseMessageShort(uint8_t *data);
      void parseMessageLong(uint8_t *data);
      void logMessageBuffer(uint8_t *data, unsigned long len);

		/* template method */
		double myPrivateMethod() {
			return 1.0;
		}   

};
#endif