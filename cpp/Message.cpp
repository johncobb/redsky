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

Message* Message::createMessage(int type) {
    return new Enfora();
}