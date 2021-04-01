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

void Response::setContenLength(std::string content)
{
	char* len;
	if (!(len = ft_itoa(content.length()))) throw Response::BuildResponseException();
	setResponse(getResponse().insert(getResponse().length(), "content-length: "));
	setResponse(getResponse().insert(getResponse().length(), len));
	setResponse(getResponse().insert(getResponse().length(), "\n"));
}

void Response::setContenType(std::string path)
{
	size_t nb = path.find_last_of(".");
	std::string type = path;
	type.erase(0, nb);
	if (!ft_strcmp(type.c_str() , ".aac"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: audio/aac\n"));
	if (!ft_strcmp(type.c_str() , ".abw"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/x-abiword\n"));
	if (!ft_strcmp(type.c_str() , ".arc"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/octet-stream\n"));
	if (!ft_strcmp(type.c_str() , ".avi"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: video/x-msvideo\n"));
	if (!ft_strcmp(type.c_str() , ".azw"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/vnd.amazon.ebook\n"));
	if (!ft_strcmp(type.c_str() , ".bin"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/octet-stream\n"));
	if (!ft_strcmp(type.c_str() , ".bmp"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: image/bmp\n"));
	if (!ft_strcmp(type.c_str() , ".bz"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/x-bzip\n"));
	if (!ft_strcmp(type.c_str() , ".bz2"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/x-bzip2\n"));
	if (!ft_strcmp(type.c_str() , ".csh"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/x-csh\n"));
	if (!ft_strcmp(type.c_str() , ".css"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: text/css\n"));
	if (!ft_strcmp(type.c_str() , ".csv"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: text/csv\n"));
	if (!ft_strcmp(type.c_str() , ".doc"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/msword\n"));
	if (!ft_strcmp(type.c_str() , ".docx"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: pplication/vnd.openxmlformats-officedocument.wordprocessingml.document\n"));
	if (!ft_strcmp(type.c_str() , ".eot"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/vnd.ms-fontobject\n"));
	if (!ft_strcmp(type.c_str() , ".epub"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/epub+zip\n"));
	if (!ft_strcmp(type.c_str() , ".gif"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: image/gif\n"));
	if (!ft_strcmp(type.c_str() , ".htm"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: text/html\n"));
	if (!ft_strcmp(type.c_str() , ".html"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: text/html\n"));
	if (!ft_strcmp(type.c_str() , ".ico"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: image/x-icon\n"));
	if (!ft_strcmp(type.c_str() , ".ics"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: text/calendar\n"));
	if (!ft_strcmp(type.c_str() , ".jar"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/java-archive\n"));
	if (!ft_strcmp(type.c_str() , ".jpg"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: image/jpeg\n"));
	if (!ft_strcmp(type.c_str() , ".jpeg"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: image/jpeg\n"));
	if (!ft_strcmp(type.c_str() , ".js"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/javascript\n"));
	if (!ft_strcmp(type.c_str() , ".json"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/json\n"));
	if (!ft_strcmp(type.c_str() , ".mid"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: audio/midi\n"));
	if (!ft_strcmp(type.c_str() , ".midi"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: audio/midi\n"));
	if (!ft_strcmp(type.c_str() , ".mpeg"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: video/mpeg\n"));
	if (!ft_strcmp(type.c_str() , ".mpkg"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/vnd.apple.installer+xml\n"));
	if (!ft_strcmp(type.c_str() , ".odp"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/vnd.oasis.opendocument.presentation\n"));
	if (!ft_strcmp(type.c_str() , ".ods"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/vnd.oasis.opendocument.spreadsheet\n"));
	if (!ft_strcmp(type.c_str() , ".odt"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/vnd.oasis.opendocument.text\n"));
	if (!ft_strcmp(type.c_str() , ".oga"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: audio/ogg\n"));
	if (!ft_strcmp(type.c_str() , ".ogv"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: video/ogg\n"));
	if (!ft_strcmp(type.c_str() , ".ogx"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/ogg\n"));
	if (!ft_strcmp(type.c_str() , ".otf"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: font/otf\n"));
	if (!ft_strcmp(type.c_str() , ".png"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: image/png\n"));
	if (!ft_strcmp(type.c_str() , ".pdf"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/pdf\n"));
	if (!ft_strcmp(type.c_str() , ".ppt"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/vnd.ms-powerpoint\n"));
	if (!ft_strcmp(type.c_str() , ".pptx"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/vnd.openxmlformats-officedocument.presentationml.presentation\n"));
	if (!ft_strcmp(type.c_str() , ".rar"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/x-rar-compressed\n"));
	if (!ft_strcmp(type.c_str() , ".rtf"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/rtf\n"));
	if (!ft_strcmp(type.c_str() , ".sh"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/x-sh\n"));
	if (!ft_strcmp(type.c_str() , ".svg"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: image/svg+xml\n"));
	if (!ft_strcmp(type.c_str() , ".swf"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/x-shockwave-flash\n"));
	if (!ft_strcmp(type.c_str() , ".tar"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/x-tar\n"));
	if (!ft_strcmp(type.c_str() , ".tif"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: image/tiff\n"));
	if (!ft_strcmp(type.c_str() , ".tiff"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: image/tiff\n"));
	if (!ft_strcmp(type.c_str() , ".ts"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/typescript\n"));
	if (!ft_strcmp(type.c_str() , ".ttf"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: font/ttf\n"));
	if (!ft_strcmp(type.c_str() , ".vsd"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/vnd.visio\n"));
	if (!ft_strcmp(type.c_str() , ".wav"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: audio/x-wav\n"));
	if (!ft_strcmp(type.c_str() , ".weba"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: audio/webm\n"));
	if (!ft_strcmp(type.c_str() , ".webm"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: video/webm\n"));
	if (!ft_strcmp(type.c_str() , ".webp"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: image/webp\n"));
	if (!ft_strcmp(type.c_str() , ".woff"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: font/woff\n"));
	if (!ft_strcmp(type.c_str() , ".woff2")) setResponse(getResponse().insert(getResponse().length(), "Content-Type: font/woff2\n"));
	if (!ft_strcmp(type.c_str() , ".xhtml")) setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/xhtml+xml\n"));
	if (!ft_strcmp(type.c_str() , ".xls"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/vnd.ms-excel\n"));
	if (!ft_strcmp(type.c_str() , ".xlsx"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet\n"));
	if (!ft_strcmp(type.c_str() , ".xml"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/xml\n"));
	if (!ft_strcmp(type.c_str() , ".xul"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/vnd.mozilla.xul+xml\n"));
	if (!ft_strcmp(type.c_str() , ".zip"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/zip\n"));
	if (!ft_strcmp(type.c_str() , ".3gp"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: video/3gpp\n"));
	if (!ft_strcmp(type.c_str() , ".3g2"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: video/3gpp2\n"));
	if (!ft_strcmp(type.c_str() , ".7z"))	 setResponse(getResponse().insert(getResponse().length(), "Content-Type: application/x-7z-compressed\n"));
}

void Response::setLastModified(std::string path)
{
	struct stat	sb;
	stat(path.c_str(), &sb);
	char *date;
	if (!(date = (char *)malloc(12))) throw Response::BuildResponseException();
	ft_bzero(date, 12);
	strftime(date, 3, "%a", gmtime(&(sb.st_ctime)));
	setResponse(getResponse().insert(getResponse().length(), "Last-Modified: "));
	setResponse(getResponse().insert(getResponse().length(), date));
	setResponse(getResponse().insert(getResponse().length(), ", "));
	ft_bzero(date, 3);
	strftime(date, 11, "%d %h %Y", gmtime(&(sb.st_ctime)));
	setResponse(getResponse().insert(getResponse().length(), date));
	setResponse(getResponse().insert(getResponse().length(), " "));
	ft_bzero(date, 11);
	strftime(date, 8, "%H:%M:%S", gmtime(&(sb.st_ctime)));
	setResponse(getResponse().insert(getResponse().length(), date));
	setResponse(getResponse().insert(getResponse().length(), " GMT"));
	free(date);
	setResponse(getResponse().insert(getResponse().length(), "\n"));
}

void Response::setLocation(std::string file, int statuCode)
{
	if ((statuCode >= 300 && statuCode < 400) || statuCode == 201)
	{
		setResponse(getResponse().insert(getResponse().length(), "Location: "));
		setResponse(getResponse().insert(getResponse().length(), file));
		setResponse(getResponse().insert(getResponse().length(), "\n"));
	}
}

void Response::setRetryAfer(int statuCode)
{
	if (statuCode == 503 || statuCode == 429 || statuCode == 301)
	{
		// std::string date;
		// setResponse(getResponse().insert(getResponse().length(), "Retry-After: "));
		// setResponse(getResponse().insert(getResponse().length(), date));
		// setResponse(getResponse().insert(getResponse().length(), "\n"));
		setResponse(getResponse().insert(getResponse().length(), "Retry-After: "));
		(void)statuCode;
		// std::string msg;
		// if (statuCode == 503) msg = ;
		// else if (statuCode == 429) msg = ;
		// else if (statuCode == 301) msg = ;
		// setResponse(getResponse().insert(getResponse().length(), msg));
		setResponse(getResponse().insert(getResponse().length(), "\n"));
	}
}

void Response::setServer()
{
	setResponse(getResponse().insert(getResponse().length(), "Server: Nginx\n"));
}

void Response::setTransfetEncoding()
{
	// setResponse(getResponse().insert(getResponse().length(), "Transfer-Encoding: "));
	// setResponse(getResponse().insert(getResponse().length(), msg));
	// setResponse(getResponse().insert(getResponse().length(), "\n"));
}

void Response::setWWWAuthenticate(int statuCode)
{
	if (statuCode == 401)
	{
		setResponse(getResponse().insert(getResponse().length(), "WWW-Authenticate: "));
		// setResponse(getResponse().insert(getResponse().length(), msg));
		setResponse(getResponse().insert(getResponse().length(), "\n"));
	}
}

std::string Response::getContent(std::string path)
{
	std::string ret;
	int fd;
	if ((fd = open(path.c_str(), O_RDONLY)) < 0) throw Response::BuildResponseException();
	char *line;
	while (get_next_line(fd, &line) > 0)
	{
		ret.insert(ret.length(), line);
		ret.insert(ret.length(), "\n");
		free(line);
	}
	close(fd);
	if (!line) throw Response::BuildResponseException();
	ret.insert(ret.length(), line);
	free(line);
	return (ret);
}

int Response::statu_code(std::string path, std::vector<Routes> *routes)
{
	struct stat	sb;
	if (stat(path.c_str(), &sb) == -1) return (404);
	if (routes)
	{
		(void)routes;
	}
	return (200);
}

void Response::getMethod(std::string file, Server *serv)
{
	std::string content;
	if (file[file.length() - 1] == '/') file.insert(file.length(), "index.html");
	std::string www = "./server/www";
	www.insert(www.length(), file);
	int statuCode = statu_code(www, serv->_routes);
	setResponse("HTTP/");
	if (statuCode == 200) setResponse(getResponse().insert(getResponse().length(), " 200 ok\n"));
	else if (statuCode == 404) setResponse(getResponse().insert(getResponse().length(), " 404 Not Found\n"));
	if (statuCode == 404) {
		www = serv->getErrorPage("404");
		if (www.empty()) www = "./server/default/error404.html";
		if (statu_code(www, NULL) == 404) throw Response::BuildResponseException();
	}
	content = getContent(www);
	setLastModified(www);
	setLocation(file, statuCode);
	setRetryAfer(statuCode);
	setServer();
	setTransfetEncoding();
	setWWWAuthenticate(statuCode);
	setContenLength(content);
	setContenType(www);
	setResponse(getResponse().insert(getResponse().length(), "\n"));
	setResponse(getResponse().insert(getResponse().length(), content));

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
	// req->verif(); // verif les HEARDERS de resquest si no host return page 400 etc...
	std::string request(req->getFirstLine());
	int space[2];
	space[0] = request.find(' ');
	space[1] = request.rfind(' ');
	std::string method = request.substr(0, space[0]);
	std::string file = request.substr(space[0] + 1, space[1] - (space[0] + 1));
	std::cout << "   \033[1;30mnew REQUEST: \033[0;33m " << method << " on " << file << "\033[0m" << std::endl;
	if (!ft_strcmp(method.c_str(), "GET")) getMethod(file, serv);
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