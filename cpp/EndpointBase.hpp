/**
 * @file Endpoint.hpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

#ifndef EndpointBase_H
#define EndpointBase_H

#include <stdint.h> 
#include "Socket.hpp"

using namespace std;

class EndpointBase {


	public:
		// todo: research initializer list for base class
		// EndpointBase();
		// EndpointBase(endpoint_t *info);

		endpoint_t * getEndpoint() {
			return endpoint;
		}

		/* template method */
		double myPublicMethod() {
			return 2.0;
		}

	protected:
		endpoint_t *endpoint;

		void setEndpoint(endpoint_t *info) {
			endpoint = info;
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