/**
 * @file Enfora.hpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <stdint.h> 

using namespace std;

class MessageBase {
	public:
		double myPublicMethod() {
			return 2.0;
		}

	private:
		
		double myPrivateMethod() {
			return 1.0;
		}
};

#endif