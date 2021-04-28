#include "../../includes/class/Server.hpp"

Server::Server()
{

}

Server::Server(const Server &other) : _error_pages(other._error_pages), _port(other._port), _host(other._host),
_server_name(other._server_name)
{
	_listen = other.getListen();
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
}

void Server::setPort(int value)
{
	this->_port = value;
}

void Server::setHost(std::string value)
{
	this->_host = value;
}

void Server::setServerName(std::string value)
{
	this->_server_name = value;
}

void Server::setErrorPages(std::list<std::string> value)
{
	this->_error_pages = value;
}

void Server::setRoutes(std::vector<Routes> value)
{
	this->_routes = value;
}

std::string Server::getListen() const
{
	return(this->_listen);
}

int Server::getPort() const
{
	return(this->_port);
}

std::string Server::getHost() const
{
	return(this->_host);
}

std::string Server::getServerName() const
{
	return(this->_server_name);
}

Routes Server::getRoute(std::string dir) const
{
	Routes tmp;
	int pnt = 0;
	int dot[2];
	dot[0] = dir.rfind('.');
	for (std::__1::vector<Routes>::const_iterator itr = _routes.begin(); itr != _routes.end(); itr++)
	{
		dot[1] = itr->getDirFile().rfind('.');
		if (dot[1] >= 0 && !ft_strcmp(&dir[dot[0]], &itr->getDirFile()[dot[1]]))
			return (*itr);
		int len = itr->getDirFile().length() > dir.length() ? dir.length() : itr->getDirFile().length();
		if (!ft_strncmp(itr->getDirFile().c_str(), dir.c_str(), len))
		{
			if (!(itr->getDirFile().length() > dir.length() && itr->getDirFile()[dir.length()] != '\0' && itr->getDirFile()[dir.length()] != '/'))
			{
				if (tmp.getDirFile().empty()) {
					tmp = *itr;
					for (int i = 0; itr->getDirFile()[i]; i++)
						if (itr->getDirFile()[i] == '/') pnt += 2;
					if (itr->getDirFile()[itr->getDirFile().length()] != '/' ) pnt++;
				}
				else {
					int cmp = 0;
					for (int i = 0; itr->getDirFile()[i]; i++)
						if (itr->getDirFile()[i] == '/') cmp += 2;
					if (itr->getDirFile()[itr->getDirFile().length()] != '/' ) cmp++;
					if (cmp > pnt)
					{
						tmp = *itr;
						pnt = cmp;
					}
				}
			}
		}
	}
	return (tmp);
}

void Server::check_config()
{
	if (this->_host.empty() && this->_port <= 0)
		throw Server::BadConfigListenException();
	if (this->_server_name.empty())
		throw Server::BadConfigServerNameException();
}

std::string Server::getErrorPage(std::string err) const
{
	std::string errpath;
	for (std::list<std::string>::const_iterator itr = _error_pages.begin(); itr != _error_pages.end(); itr++)
	{
		if (!ft_strncmp(err.c_str(), itr->c_str(), err.length()))
		{
			const char *verif = itr->c_str();
			int i = 3;
			while ((verif[i] >= 9 && verif[i]  <= 13) || verif[i]  == 32)
				i++;
			if (verif[i++] == ':')
			{
				while ((verif[i] >= 9 && verif[i]  <= 13) || verif[i]  == 32)
					i++;
				errpath = &verif[i];
			}
		}
	}
	return (errpath);
}

const char* Server::BadConfigListenException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Server haven't listen\033[0m");
}

const char* Server::BadConfigServerNameException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Server haven't name\033[0m");
}

const char* Server::SameServerNameException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Same server name\033[0m");
}