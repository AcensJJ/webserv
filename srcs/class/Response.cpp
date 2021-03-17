#include "../../includes/class/Response.hpp"

Response::Response()
{

}

Response::Response(const Response &other)
{
	_response = other.getResponse();
}

Response::~Response()
{

}

Response &Response::operator=(const Response &other)
{
    if (this == &other) return(*this);
    this->~Response();
    return *new(this) Response(other);
}

void Response::setResponse(std::string value)
{
	this->_response = value;
}

std::string Response::getResponse() const
{
	return(this->_response);
}

void Response::config_response()
{
	setResponse("HTTP/1.1 200 ok\r\n");
	setResponse(getResponse().insert(getResponse().length(), "\n"));
	setResponse(getResponse().insert(getResponse().length(), "<html>\n<body>\n<h1>Hello World!</h1>\n</body>\n</html>\n"));
	
	// struct tm tm;
    // char buf[255];
	// strftime(buf, sizeof(buf), "%Y", &tm);
    // puts(buf);

	
	// std::cout<< tm.tm_sec << "la"<< std::endl;
	// time_t rawtime;
	// struct tm * timeinfo;
	// char buffer [80];

	// time (&rawtime);
	// // timeinfo = localtime (&rawtime);

	// strftime (buffer,80,"Now it's %I:%M%p.",timeinfo);
	// puts (buffer);


}

const char* Response::BuildResponseException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Building response failed\033[0m");
}