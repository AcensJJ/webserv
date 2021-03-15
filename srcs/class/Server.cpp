#include "../../includes/class/Server.hpp"

Server::Server()
{

}

Server::Server(const Server &other) : _error_pages(other._error_pages), _port(other._port), _host(other._host),
_server_name(other._server_name), _limit_client_body(other._limit_client_body)
{
	_routes = other._routes;
}

Server::~Server()
{

}

Server &Server::operator=(const Server &other)
{
    if (this == &other) return(*this);
    this->~Server();
    return *new(this) Server(other);
}

void Server::setListen(std::string value)
{
	this->_listen = value;
};
void Server::setPort(int value)
{
	this->_port = value;
};
void Server::setHost(std::string value)
{
	this->_host = value;
};
void Server::setServerName(std::string value)
{
	this->_server_name = value;
};
void Server::setLimitClientBody(std::string value)
{
	this->_limit_client_body = value;
};
void Server::setErrorPages(std::list<std::string> value)
{
	this->_error_pages = &value;
};
void Server::setRoutes(std::vector<Routes> value)
{
	this->_routes = &value;
};

std::string Server::getListen() const
{
	return(this->_listen);
};

int Server::getPort() const
{
	return(this->_port);
};

std::string Server::getHost() const
{
	return(this->_host);
};

std::string Server::getServerName() const
{
	return(this->_server_name);
};

std::string Server::getLimitClientBody() const
{
	return(this->_limit_client_body);
};

void Server::check_config()
{
	if (this->_host.empty() && this->_port <= 0)
		throw Server::BadConfigListenException();
	if (this->_server_name.empty())
		throw Server::BadConfigServerNameException();
}

const char* Server::BadConfigListenException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Server haven't listen\033[0m");
}

const char* Server::BadConfigServerNameException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Server haven't name\033[0m");
}