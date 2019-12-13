/**
 * @file MessageBase.hpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */


#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <stdint.h>
#include "MessageFactory.hpp"

using namespace std;


class MessageBase {
    
    public:
        
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