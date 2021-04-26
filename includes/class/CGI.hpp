#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>

#include "global.hpp"

class CGI {
    public:
		CGI();
		CGI(const CGI &other);
		~CGI();
		CGI &operator=(const CGI &other);

	private:

};

#endif // !REQUEST_HPP