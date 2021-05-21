#include "../../includes/class/Server.hpp"

Server::Server()
{
	this->_server_fd = -1;
}

Server::Server(const Server &other)
{
	_error_pages = other._error_pages;
	_listen = other.getListen();
	_port = other.getPort();
	_host = other.getHost();
	_server_name = other.getServerName();
	_server_fd = other.getSocket();
	_address = other.getSockAddr();
	_readfds = other.getRdFdAddr();
	_writefds = other.getWrFdAddr();
	std::list<Routes> route;
	for (std::list<Routes>::const_iterator test = other._routes.begin(); test != other._routes.end(); test++)
	{
		Routes tmpr;
		tmpr = *test;
		route.push_back(tmpr);
	}
	_routes = route;
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

void Server::setRoutes(std::list<Routes> value)
{
	this->_routes = value;
}

void Server::setSocket(int value)
{
	this->_server_fd = value;
}

void Server::setSockAddr(sockaddr_in value)
{
	this->_address = value;
}

void Server::setRdFd(fd_set* value)
{
	this->_readfds = value;
}

void Server::setWrFd(fd_set* value)
{
	this->_writefds = value;
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
	for (std::__1::list<Routes>::const_iterator itr = _routes.begin(); itr != _routes.end(); itr++)
	{
		Routes actrt = *itr;
		dot[1] = actrt.getDirFile().rfind('.');
		if (dot[1] >= 0 && !ft_strcmp(&dir[dot[0]], &actrt.getDirFile()[dot[1]]))
			return (actrt);
		int len = actrt.getDirFile().length();
		if (!ft_strncmp(actrt.getDirFile().c_str(), dir.c_str(), len))
		{
			if (!(actrt.getDirFile().length() > dir.length() && actrt.getDirFile()[dir.length()] != '\0' && actrt.getDirFile()[dir.length()] != '/'))
			{
				if (tmp.getDirFile().empty()) {
					tmp = actrt;
					for (int i = 0; actrt.getDirFile()[i]; i++)
						if (actrt.getDirFile()[i] == '/') pnt += 2;
					if (actrt.getDirFile()[actrt.getDirFile().length()] != '/' ) pnt++;
				}
				else {
					int cmp = 0;
					for (int i = 0; actrt.getDirFile()[i]; i++)
						if (actrt.getDirFile()[i] == '/') cmp += 2;
					if (actrt.getDirFile()[actrt.getDirFile().length()] != '/' ) cmp++;
					if (cmp > pnt)
					{
						tmp = actrt;
						pnt = cmp;
					}
				}
			}
		}
	}
	return (tmp);
}

int Server::getSocket() const
{
	return (this->_server_fd);
}

sockaddr_in Server::getSockAddr() const
{
	return (this->_address);
}

fd_set	Server::getRdFd() const
{
	fd_set *tmp = getRdFdAddr();
	return (*tmp);
}

fd_set Server::getWrFd() const
{
	fd_set *tmp = getWrFdAddr();
	return (*tmp);
}

fd_set*	Server::getRdFdAddr() const
{
	return (this->_readfds);
}

fd_set* Server::getWrFdAddr() const
{
	return (this->_writefds);
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

const char* Server::SameServerNameException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Same server name\033[0m");
}