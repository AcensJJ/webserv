#include "../../includes/class/Routes.hpp"

Routes::Routes()
{
	
}

Routes::Routes(const Routes &other)  : _dir_file(other._dir_file),  _listen(other._listen), 
_default(other._default), _limit_client_body(other._limit_client_body)
{
	_location = other.getLocation();
	_cgi_path = other.getCGIPath();
	_method = other.getMethod();
}

Routes::~Routes()
{

}

Routes &Routes::operator=(const Routes &other)
{
    if (this == &other) return(*this);
    this->~Routes();
    return *new(this) Routes(other);
}

void Routes::setDirFile(std::string value)
{
	this->_dir_file = value;
}

void Routes::setListen(bool value)
{
	this->_listen = value;
}

void Routes::setDefault(std::string value)
{
	this->_default = value;
}

void Routes::setLocation(std::string value)
{
	this->_location = value;
}

void Routes::setCGIPath(std::string value)
{
	this->_cgi_path = value;
}

void Routes::setLimitClientBody(std::string value)
{
	this->_limit_client_body = value;
}

void Routes::setMethod(std::string value)
{
	this->_method = value;
}

std::string Routes::getDirFile() const
{
	return (this->_dir_file);
}

bool Routes::getListen() const
{
	return (this->_listen);
}

std::string Routes::getDefault() const
{
	return (this->_default);
}

std::string Routes::getLocation() const
{
	return (this->_location);
}

std::string Routes::getCGIPath() const
{
	return (this->_cgi_path);
}

std::string Routes::getLimitClientBody() const
{
	return(this->_limit_client_body);
}

std::string Routes::getMethod() const
{
	return(this->_method);
}
