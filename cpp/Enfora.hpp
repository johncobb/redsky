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
#include "Gps.hpp"

#define ENFORA_ATMSGSEND = "AT$MSGSND=\"{0}\"\0D\r";

using namespace std;

class Enfora {

    public:

        Enfora();
        Enfora(uint8_t *data, unsigned long len);
        
        virtual ~Enfora();

        uint8_t ver;
        uint8_t *data;
        unsigned long len;
        Gps gps;

        uint64_t identify(uint8_t *data, unsigned long len);
        void parseMessage(uint8_t *data, unsigned long len);
        

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
		/* template method */
		double myPrivateMethod() {
			return 1.0;
		}   

};
#endif