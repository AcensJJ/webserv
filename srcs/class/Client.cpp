#include "../../includes/class/Client.hpp"

Client::Client()
{

}

Client::Client(const Client &other)
{
	setRequest(other.getRequest());
	setResponse(other.getResponse());
	setSocket(other.getSocket());
}

Client::~Client()
{

}

Client &Client::operator=(const Client &other)
{
    if (this == &other) return(*this);
    this->~Client();
    return *new(this) Client(other);
}

void Client::setRequest(Request *value)
{
	this->_req = value;
}

void Client::setResponse(Response *value)
{
	this->_res = value;
}

void Client::setSocket(int value)
{
	this->_socket = value;
}

Request *Client::getRequest() const
{
	return(this->_req);
}

Response *Client::getResponse() const
{
	return(this->_res);
}

int Client::getSocket() const
{
	return(this->_socket);
}
