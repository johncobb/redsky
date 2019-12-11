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
#include "Socket.hpp"

using namespace std;

class MessageBase {


	public:
		// todo: research initializer list for base class
		// MessageBase();
		// MessageBase(socket_info_t *info);

		socket_info_t * getSocketInfo() {
			return socketInfo;
		}

		/* template method */
		double myPublicMethod() {
			return 2.0;
		}

	protected:
		socket_info_t *socketInfo;

		void setSocketInfo(socket_info_t *info) {
			socketInfo = info;
		}

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