/**
 * @file Enfora.cpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#include "Enfora.hpp"

#include <iostream>


using namespace std;

Enfora::Enfora() {
    gps = Gps();
}


Enfora::Enfora(uint8_t *data, unsigned long len):data(data), len(len) {

}


Enfora::~Enfora() {

}