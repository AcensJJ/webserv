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

void Response::setContenLength(std::string content) // not that
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
	if (!ft_strcmp(type.c_str() , ".aac"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: audio/aac; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".abw"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/x-abiword; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".arc"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/octet-stream; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".avi"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: video/x-msvideo; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".azw"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/vnd.amazon.ebook; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".bin"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/octet-stream; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".bmp"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: image/bmp; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".bz"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/x-bzip; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".bz2"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/x-bzip2; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".csh"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/x-csh; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".css"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: text/css; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".csv"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: text/csv; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".doc"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/msword; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".docx"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: pplication/vnd.openxmlformats-officedocument.wordprocessingml.document; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".eot"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/vnd.ms-fontobject; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".epub"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/epub+zip; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".gif"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: image/gif; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".htm"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: text/html; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".html"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: text/html; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".ico"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: image/x-icon; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".ics"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: text/calendar; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".jar"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/java-archive; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".jpg"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: image/jpeg; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".jpeg"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: image/jpeg; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".js"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/javascript; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".json"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/json; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".mid"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: audio/midi; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".midi"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: audio/midi; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".mpeg"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: video/mpeg; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".mpkg"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/vnd.apple.installer+xml; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".odp"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/vnd.oasis.opendocument.presentation; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".ods"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/vnd.oasis.opendocument.spreadsheet; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".odt"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/vnd.oasis.opendocument.text; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".oga"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: audio/ogg; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".ogv"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: video/ogg; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".ogx"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/ogg; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".otf"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: font/otf; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".png"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: image/png; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".pdf"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/pdf; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".ppt"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/vnd.ms-powerpoint; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".pptx"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/vnd.openxmlformats-officedocument.presentationml.presentation; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".rar"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/x-rar-compressed; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".rtf"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/rtf; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".sh"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/x-sh; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".svg"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: image/svg+xml; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".swf"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/x-shockwave-flash; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".tar"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/x-tar; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".tif"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: image/tiff; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".tiff"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: image/tiff; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".ts"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/typescript; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".ttf"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: font/ttf; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".vsd"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/vnd.visio; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".wav"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: audio/x-wav; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".weba"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: audio/webm; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".webm"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: video/webm; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".webp"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: image/webp; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".woff"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: font/woff; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".woff2")) setResponse(getResponse().insert(getResponse().length(), "content-type: font/woff2; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".xhtml")) setResponse(getResponse().insert(getResponse().length(), "content-type: application/xhtml+xml; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".xls"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/vnd.ms-excel; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".xlsx"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".xml"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/xml; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".xul"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/vnd.mozilla.xul+xml; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".zip"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/zip; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".3gp"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: video/3gpp; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".3g2"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: video/3gpp2; charset=UTF-8\n"));
	if (!ft_strcmp(type.c_str() , ".7z"))	 setResponse(getResponse().insert(getResponse().length(), "content-type: application/x-7z-compressed; charset=UTF-8\n"));
}

void Response::setLastModified(std::string path)
{
	struct stat	sb;
	stat(path.c_str(), &sb);
	char *date;
	if (!(date = (char *)malloc(13))) throw Response::BuildResponseException();
	ft_bzero(date, 13);
	strftime(date, 4, "%a", gmtime(&(sb.st_ctime)));
	setResponse(getResponse().insert(getResponse().length(), "last-modified: "));
	setResponse(getResponse().insert(getResponse().length(), date));
	setResponse(getResponse().insert(getResponse().length(), ", "));
	ft_bzero(date, 4);
	strftime(date, 13, "%d %h %Y", gmtime(&(sb.st_ctime)));
	setResponse(getResponse().insert(getResponse().length(), date));
	setResponse(getResponse().insert(getResponse().length(), " "));
	ft_bzero(date, 13);
	strftime(date, 9, "%H:%M:%S", gmtime(&(sb.st_ctime)));
	setResponse(getResponse().insert(getResponse().length(), date));
	setResponse(getResponse().insert(getResponse().length(), " GMT"));
	free(date);
	setResponse(getResponse().insert(getResponse().length(), "\n"));
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
		free(line);
	}
	close(fd);
	if (!line) throw Response::BuildResponseException();
	ret.insert(ret.length(), line);
	free(line);
	return (ret);
}

int Response::statu_code(std::string path)
{
	struct stat	sb;
	if (stat(path.c_str(), &sb) == -1) return (404);
	return (200);
}

void Response::getMethod(std::string file, Server *serv)
{
	std::string content;
	if (file.empty()) file = "index.html";
	if (file[file.length() - 1] == '/') file.insert(file.length(), "index.html");
	std::string www = "./server/www";
	www.insert(www.length(), file);
	(void)serv;
	// int statuCode = statu_code(www);
	// setResponse("HTTP/");
	// if (statuCode == 200){
	// 	setResponse(getResponse().insert(getResponse().length(), " 200 ok\n"));
		// setLastModified(www);
	// }
	// else if (statuCode == 404) setResponse(getResponse().insert(getResponse().length(), " 404 Not Found\n"));
	// if (statuCode == 404) {
	// 	std::string errpath = serv->getErrorPage("404");
	// 	if (errpath.empty()) content = getContent("./server/default/error404.html");
	// 	else if (statu_code(errpath) == 200) content = getContent(errpath);
	// 	else throw Response::BuildResponseException();
	// }
	// if (statuCode == 200) content = getContent(www);
	// setContenLength(content);
	// setContenType(www);
	// setResponse(getResponse().insert(getResponse().length(), "\n"));
	// setResponse(getResponse().insert(getResponse().length(), content));

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