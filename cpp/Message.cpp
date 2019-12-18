/**
 * @file Message.cpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#include <iostream>
#include "Message.hpp"
#include "Enfora.hpp"


using namespace std;

Message::Message() {
    queue_complete = false;
}

Message* Message::createMessage(uint8_t *data, unsigned long len) {
    
    Message *msg = NULL;

    MessageType type = identify(data, len);
    if (type == TEnfora) {
        msg = new Enfora(data, len);
        return msg;
        // return new Enfora(data, len);
    } else {
        cout << "createMessage Unknown" << endl;
    }
    return NULL;
}

Message* Message::createMessage(uint8_t *data, unsigned long len, Endpoint *target) {
    
    Message *msg = NULL;

    msg = Message::createMessage(data, len);

    if (msg != NULL) {
        /* log server time */
        msg->timestamp = clock();    
        /* we need to record the client id parsed form the valid message */
        target->clientId = msg->id;

    }
    
    return msg;
}

MessageType Message::identify(uint8_t *data, unsigned long len) {
    if (len >= 4) {
        if (data[0] == 0x00 && data[1] == 0x05 && data[2] == 0x02 && data[3] == 0x00) {
            return TEnfora;
        }
    }

    return TUnknown;
}