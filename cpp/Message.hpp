/**
 * @file Message.hpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */


#ifndef MESSAGE_H
#define MESSAGE_H

enum MessageType {
    TUnknown, TEnfora, TCalAmp, TAntx
};

class Message {
    public:

        Message();

        clock_t timestamp;
        bool queue_complete;

        static Message *createMessage(uint8_t *data, unsigned long len);


    protected:

        static MessageType identify(uint8_t *data, unsigned long len);
        

};

#endif