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

void Response::set_lastModified(std::string path)
{
	struct stat	sb;
	stat(path.c_str(), &sb);
	char date[10];
	strftime(date, 10, "%d-%m-%y", gmtime(&(sb.st_ctime)));
	printf("The file %s was last modified at %s|\n", path.c_str(), date);
	setResponse(getResponse().insert(getResponse().length(), "Last-Modified: "));
	setResponse(getResponse().insert(getResponse().length(), date));
	date[0] = 0;
	setResponse(getResponse().insert(getResponse().length(), "\n"));
}

void Response::set_content(std::string path)
{
	int fd;
	if ((fd = open(path.c_str(), O_RDONLY)) < 0) throw Response::BuildResponseException();
	char *line;
	while (get_next_line(fd, &line) > 0)
	{
		setResponse(getResponse().insert(getResponse().length(), line));
		free(line);
	}
	if (!line) throw Response::BuildResponseException();
	setResponse(getResponse().insert(getResponse().length(), line));
	free(line);
}

int Response::statu_code(std::string path)
{
	struct stat	sb;
	if (stat(path.c_str(), &sb) == -1) return (404);
	return (200);
}

void Response::get_method(std::string file, Server *serv)
{
	if (file.empty()) file = "index.html";
	if (file[file.length() - 1] == '/') file.insert(file.length(), "index.html");
	std::string www = "./server/www";
	www.insert(www.length(), file);
	int statuCode = statu_code(www);
	setResponse("HTTP/");
	if (statuCode == 200){
		setResponse(getResponse().insert(getResponse().length(), " 200 ok\n"));
		set_lastModified(www);
	}
	else if (statuCode == 404) setResponse(getResponse().insert(getResponse().length(), " 404 Not Found\n"));
	setResponse(getResponse().insert(getResponse().length(), "\n"));
	if (statuCode == 404) {
		std::string errpath = serv->getErrorPage("404");
		if (errpath.empty()) set_content("./server/default/error404.html");
		else if (statu_code(errpath) == 200) set_content(errpath);
		else throw Response::BuildResponseException();
	}
	if (statuCode == 200) set_content(www);
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

void Response::config_response(Request *req, Server *serv)
{
	std::string request(req->getFirstLine());
	int space[2];
	space[0] = request.find(' ');
	space[1] = request.rfind(' ');
	std::string method = request.substr(0, space[0]);
	std::string file = request.substr(space[0] + 1, space[1] - (space[0] + 1));
	std::cout << "   \033[1;30mnew REQUEST: \033[0;33m " << method << " on " << file << "\033[0m" << std::endl;
	if (!ft_strcmp(method.c_str(), "GET")) get_method(file, serv);
	else if (!ft_strcmp(method.c_str(), "HEAD")) head_method();
	else if (!ft_strcmp(method.c_str(), "PUT")) put_method();
	else if (!ft_strcmp(method.c_str(), "DELETE")) delete_method();
	else if (!ft_strcmp(method.c_str(), "CONNECT")) connect_method();
	else if (!ft_strcmp(method.c_str(), "OPTIONS")) options_method();
	else if (!ft_strcmp(method.c_str(), "TRACE")) trace_method();
	std::cout << "   \033[1;34mRESPONSE: \033[0;34m" << std::endl << "\033[0m{\033[3;36m" << getResponse() << "\033[0m}" << std::endl;

}

const char* Response::BuildResponseException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Building response failed\033[0m");
}