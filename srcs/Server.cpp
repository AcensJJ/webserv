#include "Server.hpp"

// COPLIEN
Server::Server()
{

}

Server::Server(const Server &other) : _port(other._port), _host(other._host), _server_name(other._server_name),
_limit_client_body(other._limit_client_body), _error_pages(other._error_pages)
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

// SET
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

// GET
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

// OTHER
int Server::check_config()
{
	// checking listen (port / host)
	if (this->_host.empty() && this->_port > 0)
	{
		std::cout << "\033[1;31m   Error: \033[0;31m Server haven't listen\033[0m" << std::endl;
		return (-1);
	}
	// checking serv name
	if (this->_server_name.empty())
	{
		std::cout << "\033[1;31m   Error: \033[0;31m Server haven't name\033[0m" << std::endl;
		return (-1);
	}

	// checking error pages and if the pages exist

	// checking location

	// all good
	return (0);
}
