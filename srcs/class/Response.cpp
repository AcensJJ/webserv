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

void Response::config_response(Request req)
{
	setResponse("HTTP/1.1 200\r\n");
	if (!req.getAcceptCharsets().empty()) setResponse(getResponse().insert(getResponse().length(), req.getAcceptCharsets().insert(req.getAcceptCharsets().length(), "\n")));
	// if (!req.getAcceptLanguage().empty()) setResponse(getResponse().insert(getResponse().length(), req.getAcceptLanguage().insert(req.getAcceptLanguage().length(), "\n")));
	// if (!req.getAllow().empty()) setResponse(getResponse().insert(getResponse().length(), req.getAllow().insert(req.getAllow().length(), "\n")));
	// if (!req.getAuthorization().empty()) setResponse(getResponse().insert(getResponse().length(), req.getAuthorization().insert(req.getAuthorization().length(), "\n")));
	// if (!req.getContentLanguage().empty()) setResponse(getResponse().insert(getResponse().length(), req.getContentLanguage().insert(req.getContentLanguage().length(), "\n")));
	// if (!req.getContentLength().empty()) setResponse(getResponse().insert(getResponse().length(), req.getContentLength().insert(req.getContentLength().length(), "\n")));
	// if (!req.getContentLocation().empty()) setResponse(getResponse().insert(getResponse().length(), req.getContentLocation().insert(req.getContentLocation().length(), "\n")));
	// if (!req.getContentType().empty()) setResponse(getResponse().insert(getResponse().length(), req.getContentType().insert(req.getContentType().length(), "\n")));
	// if (!req.getDate().empty()) setResponse(getResponse().insert(getResponse().length(), req.getDate().insert(req.getDate().length(), "\n")));
	// if (!req.getHost().empty()) setResponse(getResponse().insert(getResponse().length(), req.getHost().insert(req.getHost().length(), "\n")));
	// if (!req.getLastModified().empty()) setResponse(getResponse().insert(getResponse().length(), req.getLastModified().insert(req.getLastModified().length(), "\n")));
	// if (!req.getLocation().empty()) setResponse(getResponse().insert(getResponse().length(), req.getLocation().insert(req.getLocation().length(), "\n")));
	// if (!req.getReferer().empty()) setResponse(getResponse().insert(getResponse().length(), req.getReferer().insert(req.getReferer().length(), "\n")));
	// if (!req.getRetryAfter().empty()) setResponse(getResponse().insert(getResponse().length(), req.getRetryAfter().insert(req.getRetryAfter().length(), "\n")));
	// if (!req.getServer().empty()) setResponse(getResponse().insert(getResponse().length(), req.getServer().insert(req.getServer().length(), "\n")));
	// if (!req.getTransferEncoding().empty()) setResponse(getResponse().insert(getResponse().length(), req.getTransferEncoding().insert(req.getTransferEncoding().length(), "\n")));
	// if (!req.getUserAgent().empty()) setResponse(getResponse().insert(getResponse().length(), req.getUserAgent().insert(req.getUserAgent().length(), "\n")));
	// if (!req.getWWWAuthenticate().empty()) setResponse(getResponse().insert(getResponse().length(), req.getWWWAuthenticate().insert(req.getWWWAuthenticate().length(), "\n")));
	// setResponse(getResponse().insert(getResponse().length(), "\n"));
	std::cout<<std::endl<<std::endl << getResponse()<<std::endl<<std::endl;


}

const char* Response::BuildResponseException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Building response failed\033[0m");
}