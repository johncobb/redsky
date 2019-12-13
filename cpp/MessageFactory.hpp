/**
 * @file MessageFactory.hpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */


#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include <stdint.h>
#include "Endpoint.hpp"


#include "MessageBase.hpp"
#include "Enfora.hpp"
using namespace std;


class MessageFactory {
    
    public:
        enum MessageType {
            TypeUnknown, TypeEnfora, TypeCalAmp, TypeAntx
        };

        MessageFactory();

        virtual ~MessageFactory();
        
        /*
         * Identify incoming message by endpoint address and port
         */
        MessageType identify(Endpoint *ep);
        /*
         * Identify incoming message the data
         */        
        MessageType identify(uint8_t *data, unsigned long len);

        MessageType identify(int type);

        // MessageBase* createMessage();

        double myPublicMethod() {
            return 3.0;
        }

    protected:
        double myProtectedMethod() {
            return 2.0;
        }

    private:
        double myPrivateMethod() {
            return 1.0;
        }

};

#endif