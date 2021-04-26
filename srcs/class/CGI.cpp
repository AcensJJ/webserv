#include "../../includes/class/CGI.hpp"

CGI::CGI()
{

}

CGI::CGI(const CGI &other)
{
	(void)other;
}

CGI::~CGI()
{

}

CGI &CGI::operator=(const CGI &other)
{
    if (this == &other) return(*this);
    this->~CGI();
    return *new(this) CGI(other);
}
