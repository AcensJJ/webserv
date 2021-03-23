#include "../../includes/class/Response.hpp"

Response::Response()
{

}

Response::Response(const Response &other)
{
	_response = other.getResponse();
}

Response::~Response()
{

}

Response &Response::operator=(const Response &other)
{
    if (this == &other) return(*this);
    this->~Response();
    return *new(this) Response(other);
}

void Response::setResponse(std::string value)
{
	this->_response = value;
}

std::string Response::getResponse() const
{
	return(this->_response);
}

int Response::statu_code(std::string path)
{
	struct stat	sb;
	if (stat(path.c_str(), &sb) == -1) return (404); // file not found
	return (200); // ok
}

void Response::get_method(std::string file, Server *serv)
{
	(void)serv;
	if (file.empty()) file = "index.html";
	if (file[file.length() - 1] == '/') file.insert(file.length(), "index.html");
	std::string www = "./server/www/";
	www.insert(www.length(), file);
	int statuCode = statu_code(www);
	setResponse("HTTP/1.1");
	if (statuCode == 200) setResponse(getResponse().insert(getResponse().length(), " 200 ok\n"));
	else if (statuCode == 404) setResponse(getResponse().insert(getResponse().length(), " 404 Not Found\n"));
	setResponse(getResponse().insert(getResponse().length(), "\n"));
	if (statuCode == 404) setResponse(getResponse().insert(getResponse().length(), "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\n<html>\n<body>\n<h1>404!</h1>\n</body>\n</html>\n"));
	if (statuCode == 200) setResponse(getResponse().insert(getResponse().length(), "<html>\n<body>\n<h1>Hello World!</h1>\n</body>\n</html>\n"));
}

void Response::head_method()
{
	;
}

void Response::put_method()
{
	;
}

void Response::delete_method()
{
	;
}

void Response::connect_method()
{
	;
}

void Response::options_method()
{
	;
}

void Response::trace_method()
{
	;
}

// void Response::unknow_method() // error 400
// {
// 	;
// }

void Response::config_response(Request *req, Server *serv)
{
	std::string request(req->getFirstLine());
	int space[2];
	space[0] = request.find(' ');
	space[1] = request.rfind(' ');
	std::string method = request.substr(0, space[0]);
	std::string file = request.substr(space[0] + 1, space[1] - (space[0] + 1));
	if (!ft_strcmp(method.c_str(), "GET")) get_method(file, serv);
	else if (!ft_strcmp(method.c_str(), "HEAD")) head_method();
	else if (!ft_strcmp(method.c_str(), "PUT")) put_method();
	else if (!ft_strcmp(method.c_str(), "DELETE")) delete_method();
	else if (!ft_strcmp(method.c_str(), "CONNECT")) connect_method();
	else if (!ft_strcmp(method.c_str(), "OPTIONS")) options_method();
	else if (!ft_strcmp(method.c_str(), "TRACE")) trace_method();
	// else unknow_method();
}

const char* Response::BuildResponseException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Building response failed\033[0m");
}