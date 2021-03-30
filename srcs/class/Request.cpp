#include "../../includes/class/Request.hpp"

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
	_referer = other.getReferer();
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

void Request::setFirstLine(std::string value)
{
	this->_firstLine = value;
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

void Request::setReferer(std::string value)
{
	this->_referer = value;
}

std::string Request::getFirstLine() const
{
	return(this->_firstLine);
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

std::string Request::getReferer() const
{
	return(this->_referer);
}

void Request::set_line_config(char *line)
{
	char	*temp;
	
	if (getFirstLine().empty())
		setFirstLine(line);
	else {
		temp = (char *)"Accept-Charset:";
		if (!ft_strncmp(line, temp, ft_strlen(temp)))
			setAcceptCharsets(line);
		temp = (char *)"Accept-Language:";
		if (!ft_strncmp(line, temp, ft_strlen(temp)))
			setAcceptLanguage(line);
		temp = (char *)"Allow:";
		if (!ft_strncmp(line, temp, ft_strlen(temp)))
			setAllow(line);
		temp = (char *)"Authorization:";
		if (!ft_strncmp(line, temp, ft_strlen(temp)))
			setAuthorization(line);
		temp = (char *)"Content-Language:";
		if (!ft_strncmp(line, temp, ft_strlen(temp)))
			setContentLanguage(line);
		temp = (char *)"Content-Length:";
		if (!ft_strncmp(line, temp, ft_strlen(temp)))
			setContentLength(line);
		temp = (char *)"Content-Location:";
		if (!ft_strncmp(line, temp, ft_strlen(temp)))
			setContentLocation(line);
		temp = (char *)"Content-Type:";
		if (!ft_strncmp(line, temp, ft_strlen(temp)))
			setContentType(line);
		temp = (char *)"Date:";
		if (!ft_strncmp(line, temp, ft_strlen(temp)))
			setDate(line);
		temp = (char *)"Host:";
		if (!ft_strncmp(line, temp, ft_strlen(temp)))
			setHost(line);
		temp = (char *)"Referer:";
		if (!ft_strncmp(line, temp, ft_strlen(temp)))
			setReferer(line);
	}
	free(line);
}

void Request::config_request(int fd)
{
	char *line;

	while (get_next_line(fd, &line) > 0)
		set_line_config(line);
	if (line) set_line_config(line);
	else throw Request::GNLMallocException();
}

const char* Request::GNLMallocException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m GNL malloc failed\033[0m");
}