#include "../../includes/class/Request.hpp"

Request::Request()
{

}

Request::Request(const Request &other)
{
	if (!other.getFirstLine().empty()) _firstLine = other.getFirstLine();
	if (!other.getAcceptCharsets().empty()) _acceptCharsets = other.getAcceptCharsets();
	if (!other.getAcceptLanguage().empty()) _acceptLanguage = other.getAcceptLanguage();
	if (!other.getAuthorization().empty()) _authorization = other.getAuthorization();
	if (!other.getDate().empty()) _date = other.getDate();
	if (!other.getHost().empty()) _host = other.getHost();
	if (!other.getUserAgent().empty()) _userAgent = other.getUserAgent();
	if (!other.getTransferEncoding().empty()) _userAgent = other.getTransferEncoding();
	if (!other.getReferer().empty()) _userAgent = other.getReferer();
	if (!other.getBody().empty()) _body = other.getBody();
	if (other.getTime()) _time = other.getTime();
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

void Request::setAuthorization(std::string value)
{
	this->_authorization = value;
}

void Request::setDate(std::string value)
{
	this->_date = value;
}

void Request::setHost(std::string value)
{
	this->_host = value;
}

void Request::setUserAgent(std::string value)
{
	this->_userAgent = value;
}

void Request::setTransferEncoding(std::string value)
{
	this->_transferEncoding = value;
}

void Request::setReferer(std::string value)
{
	this->_referer = value;
}

void Request::setBody(std::string value)
{
	this->_body = value;
}

void Request::setTime(int value)
{
	this->_time = value;
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

std::string Request::getAuthorization() const
{
	return(this->_authorization);
}

std::string Request::getDate() const
{
	return(this->_date);
}

std::string Request::getHost() const
{
	return(this->_host);
}

std::string Request::getUserAgent() const
{
	return(this->_userAgent);
}

std::string Request::getTransferEncoding() const
{
	return(this->_transferEncoding);
}

std::string Request::getReferer() const
{
	return(this->_referer);
}

std::string Request::getBody() const
{
	return(this->_body);
}

int			Request::getTime() const
{
	return(this->_time);
}

void Request::set_line_config(std::string line, bool body)
{
	line.erase(line.length() - 1, 1);
	if (body)
	{
		setBody(getBody().insert(getBody().length(), line));
		setBody(getBody().insert(getBody().length(), "\n"));
	}
	else if (getFirstLine().empty())
		setFirstLine(line);
	else {
		if (!ft_strncmp(line.c_str(), "Accept-Charset:", ft_strlen("Accept-Charset:")))
			setAcceptCharsets(line);
		else if (!ft_strncmp(line.c_str(), "Accept-Language:", ft_strlen("Accept-Language:")))
			setAcceptLanguage(line);
		else if (!ft_strncmp(line.c_str(), "Authorization:", ft_strlen("Authorization:")))
			setAuthorization(line);
		else if (!ft_strncmp(line.c_str(), "Date:", ft_strlen("Date:")))
			setDate(line);
		else if (!ft_strncmp(line.c_str(), "Host:", ft_strlen("Host:")))
			setHost(line);
		else if (!ft_strncmp(line.c_str(), "User-Agent:", ft_strlen("User-Agent:")))
			setUserAgent(line);
		else if (!ft_strncmp(line.c_str(), "Transfer-Encoding:", ft_strlen("Transfer-Encoding:")))
			setTransferEncoding(line);
		else if (!ft_strncmp(line.c_str(), "Referer:", ft_strlen("Referer:")))
			setReferer(line);
	}
}

void Request::config_request(std::string file)
{
	std::ifstream fd(file);
	std::string line;
	bool body(false);
	if (!_firstLine.empty()) _firstLine.clear();
	if (!_acceptCharsets.empty()) _acceptCharsets.clear();
	if (!_acceptLanguage.empty()) _acceptLanguage.clear();
	if (!_authorization.empty()) _authorization.clear();
	if (!_date.empty()) _date.clear();
	if (!_host.empty()) _host.clear();
	if (!_userAgent.empty()) _userAgent.clear();
	if (!_transferEncoding.empty()) _transferEncoding.clear();
	if (!_referer.empty()) _referer.clear();
	if (!_body.empty()) _body.clear();
	while (getline(fd, line))
	{
		set_line_config(line, body);
		if (line[0] == '\r') body = true;
		line.clear();
	}
	fd.close();
}

const char* Request::GNLMallocException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;3ii1m GNL malloc failed\033[0m");
}