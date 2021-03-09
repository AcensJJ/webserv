#include "Server.hpp"

Routes::Routes()
{
	
}

Routes::Routes(const Routes &other)  : _http_method(other._http_method), _dir_file(other._dir_file),
 _listen(other._listen),  _default(other._default)
{

}

Routes::~Routes()
{

}

Routes &Routes::operator=(const Routes &other)
{
    if (this == &other) return(*this);
    this->~Routes();
    return *new(this) Routes(other);
}

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
