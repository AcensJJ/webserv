#include "../../includes/class/Client.hpp"

Client::Client()
{

}

Client::Client(const Client &other)
{
	setRequest(other.getRequest());
	setSocket(other.getSocket());
	setTimeout(other.getTimeout());
	setDir(other.getDir());
	setTimeout(other.getTimeout());
	setRecvEnd(other.getRecvEnd());
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

Client::Client(int socket)
{
	Request req;
	struct timeval time;
	gettimeofday(&time, NULL);
	req.setTime(time.tv_sec);
	Response res;
	setRequest(&req);
	setSocket(socket);
	setTimeout(0);
	setRecvEnd(0);
}


void Client::setRequest(Request *value)
{
	this->_req = value;
}

void Client::setSocket(int value)
{
	this->_socket = value;
}

void Client::setTimeout(int value)
{
	this->_timeout = value;
}

void	Client::setDir(std::string value)
{
	this->_dir = value;
}

void Client::setRecvEnd(int value)
{
	this->_recvEnd = value;
}

Request *Client::getRequest() const
{
	return(this->_req);
}

int Client::getSocket() const
{
	return(this->_socket);
}

int Client::getTimeout() const
{
	return(this->_timeout);
}

std::string Client::getDir() const
{
	return(this->_dir);
}

int Client::getRecvEnd() const
{
	return(this->_recvEnd);
}
