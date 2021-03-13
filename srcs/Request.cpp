#include "Request.hpp"

Request::Request()
{

}

Request::Request(const Request &other)
{
	_acceptCharsets = other.getAcceptCharsets();
	_acceptLanguage = other.getAcceptLanguage();
	_allow = other.getAllow();
	_authorization = other.getAuthorization();
	_contentLanguage = other.getContentLanguage();
	_contentLength = other.getContentLength();
	_contentLocation = other.getContentLocation();
	_contentType = other.getContentType();
	_date = other.getDate();
	_host = other.getHost();
	_lastModified = other.getLastModified();
	_location = other.getLocation();
	_referer = other.getReferer();
	_retryAfter = other.getRetryAfter();
	_server = other.getServer();
	_transferEncoding = other.getTransferEncoding();
	_userAgent = other.getUserAgent();
	_wwwAuthenticate = other.getWWWAuthenticate();
}

Request::~Request()
{

}

Request &Request::operator=(const Request &other)
{
    if (this == &other) return(*this);
    this->~Request();
    return *new(this) Request(other);
}

void Request::setAcceptCharsets(std::string value)
{
	this->_acceptCharsets = value;
}

void Request::setAcceptLanguage(std::string value)
{
	this->_acceptLanguage = value;
}

void Request::setAllow(std::string value)
{
	this->_allow = value;
}

void Request::setAuthorization(std::string value)
{
	this->_authorization = value;
}

void Request::setContentLanguage(std::string value)
{
	this->_contentLanguage = value;
}

void Request::setContentLength(std::string value)
{
	this->_contentLength = value;
}

void Request::setContentLocation(std::string value)
{
	this->_contentLocation = value;
}

void Request::setContentType(std::string value)
{
	this->_contentType = value;
}

void Request::setDate(std::string value)
{
	this->_date = value;
}

void Request::setHost(std::string value)
{
	this->_host = value;
}

void Request::setLastModified(std::string value)
{
	this->_lastModified = value;
}

void Request::setLocation(std::string value)
{
	this->_location = value;
}

void Request::setReferer(std::string value)
{
	this->_referer = value;
}

void Request::setRetryAfter(std::string value)
{
	this->_retryAfter = value;
}

void Request::setServer(std::string value)
{
	this->_server = value;
}

void Request::setTransferEncoding(std::string value)
{
	this->_transferEncoding = value;
}

void Request::setUserAgent(std::string value)
{
	this->_userAgent = value;
}

void Request::setWWWAuthenticate(std::string value)
{
	this->_wwwAuthenticate = value;
}

std::string Request::getAcceptCharsets() const
{
	return(this->_acceptCharsets);
}

std::string Request::getAcceptLanguage() const
{
	return(this->_acceptLanguage);
}

std::string Request::getAllow() const
{
	return(this->_allow);
}

std::string Request::getAuthorization() const
{
	return(this->_authorization);
}

std::string Request::getContentLanguage() const
{
	return(this->_contentLanguage);
}

std::string Request::getContentLength() const
{
	return(this->_contentLength);
}

std::string Request::getContentLocation() const
{
	return(this->_contentLocation);
}

std::string Request::getContentType() const
{
	return(this->_contentType);
}

std::string Request::getDate() const
{
	return(this->_date);
}

std::string Request::getHost() const
{
	return(this->_host);
}

std::string Request::getLastModified() const
{
	return(this->_lastModified);
}

std::string Request::getLocation() const
{
	return(this->_location);
}

std::string Request::getReferer() const
{
	return(this->_referer);
}

std::string Request::getRetryAfter() const
{
	return(this->_retryAfter);
}

std::string Request::getServer() const
{
	return(this->_server);
}

std::string Request::getTransferEncoding() const
{
	return(this->_transferEncoding);
}

std::string Request::getUserAgent() const
{
	return(this->_userAgent);
}

std::string Request::getWWWAuthenticate() const
{
	return(this->_wwwAuthenticate);
}

// void config_request(int fd)
// {
// 	// while (get_next_line());
// }
