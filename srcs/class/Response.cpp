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


void Response::setDate()
{
	char buf[30];
	struct timeval tv;
	time_t curtime;

	gettimeofday(&tv, NULL); 
	curtime=tv.tv_sec;
	setResponse(getResponse().insert(getResponse().length(), "Date: "));
	strftime(buf,sizeof(buf),"%a, %d %b %Y %H:%M:%S GMT",localtime(&curtime));
	setResponse(getResponse().insert(getResponse().length(), buf));
	setResponse(getResponse().insert(getResponse().length(), "\n"));
}

void	Response::setContentLanguage(Request *req)
{
	if (!req->getAcceptLanguage().empty())
	{
		setResponse(getResponse().insert(getResponse().length(), "Content-Langage: "));
		int sep[2];
		sep[0] = 16;
		sep[1] = req->getAcceptLanguage().find(',');
		if (sep[1] == -1) sep[1] = req->getAcceptLanguage().length();
		std::string language = req->getAcceptLanguage().substr(sep[0] + 1, sep[1] - (sep[0] + 1));
		setResponse(getResponse().insert(getResponse().length(), language));
		setResponse(getResponse().insert(getResponse().length(), "\n"));
	}
}

void Response::setContentLength(std::string content)
{
	char* len;
	if (!(len = ft_itoa(content.length()))) throw Response::BuildResponseException();
	setResponse(getResponse().insert(getResponse().length(), "Content-Length: "));
	setResponse(getResponse().insert(getResponse().length(), len));
	setResponse(getResponse().insert(getResponse().length(), "\n"));
	free(len);
}

void Response::setContentLocation(std::string file)
{
	setResponse(getResponse().insert(getResponse().length(), "Content-Location: "));
	setResponse(getResponse().insert(getResponse().length(), file));
	setResponse(getResponse().insert(getResponse().length(), "\n"));
}

void Response::setContentType(std::string path, Request *req)
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
	if (!req->getAcceptCharsets().empty())
	{
		setResponse(getResponse().insert(getResponse().length() - 1, "; charset="));
		int sep[2];
		sep[0] = 15;
		sep[1] = req->getAcceptCharsets().find(',');
		if (sep[1] == -1) sep[1] = req->getAcceptCharsets().length();
		std::string charset = req->getAcceptCharsets().substr(sep[0] + 1, sep[1] - (sep[0] + 1));
		setResponse(getResponse().insert(getResponse().length() - 1, charset));
	}
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
	if ((statuCode >= 301 && statuCode <= 308) || statuCode == 201)
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

void Response::setFirstLine(int statuCode)
{
	setResponse("HTTP/1.1");
	if      (statuCode == 100) setResponse(getResponse().insert(getResponse().length(), " 100 Continue\n"));
	else if (statuCode == 101) setResponse(getResponse().insert(getResponse().length(), " 200 Switching Protocols\n"));
	else if (statuCode == 103) setResponse(getResponse().insert(getResponse().length(), " 200 Ear;y Hints\n"));
	else if (statuCode == 200) setResponse(getResponse().insert(getResponse().length(), " 200 OK\n"));
	else if (statuCode == 201) setResponse(getResponse().insert(getResponse().length(), " 201 Created\n"));
	else if (statuCode == 202) setResponse(getResponse().insert(getResponse().length(), " 202 Accepted\n"));
	else if (statuCode == 203) setResponse(getResponse().insert(getResponse().length(), " 203 Non-Authoritative Information\n"));
	else if (statuCode == 204) setResponse(getResponse().insert(getResponse().length(), " 204 No Content\n"));
	else if (statuCode == 205) setResponse(getResponse().insert(getResponse().length(), " 205 Reset Content\n"));
	else if (statuCode == 206) setResponse(getResponse().insert(getResponse().length(), " 206 Partial Content\n"));
	else if (statuCode == 300) setResponse(getResponse().insert(getResponse().length(), " 300 Multiple Choices\n"));
	else if (statuCode == 301) setResponse(getResponse().insert(getResponse().length(), " 301 Moved Permanently\n"));
	else if (statuCode == 302) setResponse(getResponse().insert(getResponse().length(), " 302 Found\n"));
	else if (statuCode == 303) setResponse(getResponse().insert(getResponse().length(), " 303 See Other\n"));
	else if (statuCode == 304) setResponse(getResponse().insert(getResponse().length(), " 304 Not Modified\n"));
	else if (statuCode == 307) setResponse(getResponse().insert(getResponse().length(), " 307 Temporary Redirect\n"));
	else if (statuCode == 308) setResponse(getResponse().insert(getResponse().length(), " 308 Permanent Redirect\n"));
	else if (statuCode == 400) setResponse(getResponse().insert(getResponse().length(), " 400 Bad Request\n"));
	else if (statuCode == 401) setResponse(getResponse().insert(getResponse().length(), " 401 Unauthoriwed\n"));
	else if (statuCode == 402) setResponse(getResponse().insert(getResponse().length(), " 402 Payment Required\n"));
	else if (statuCode == 403) setResponse(getResponse().insert(getResponse().length(), " 403 Forbidden\n"));
	else if (statuCode == 404) setResponse(getResponse().insert(getResponse().length(), " 404 Not Found\n"));
	else if (statuCode == 405) setResponse(getResponse().insert(getResponse().length(), " 405 Method Not Allowed\n"));
	else if (statuCode == 406) setResponse(getResponse().insert(getResponse().length(), " 406 Not Acceptable\n"));
	else if (statuCode == 407) setResponse(getResponse().insert(getResponse().length(), " 407 Proxy Authentication Required\n"));
	else if (statuCode == 408) setResponse(getResponse().insert(getResponse().length(), " 408 Request Timeout\n"));
	else if (statuCode == 409) setResponse(getResponse().insert(getResponse().length(), " 409 Conflict\n"));
	else if (statuCode == 410) setResponse(getResponse().insert(getResponse().length(), " 410 Gone\n"));
	else if (statuCode == 411) setResponse(getResponse().insert(getResponse().length(), " 411 Length Required\n"));
	else if (statuCode == 412) setResponse(getResponse().insert(getResponse().length(), " 412 Precondition Failed\n"));
	else if (statuCode == 413) setResponse(getResponse().insert(getResponse().length(), " 413 Payload Too Large\n"));
	else if (statuCode == 414) setResponse(getResponse().insert(getResponse().length(), " 414 URI Too Long\n"));
	else if (statuCode == 415) setResponse(getResponse().insert(getResponse().length(), " 415 Unsupported Media Type\n"));
	else if (statuCode == 416) setResponse(getResponse().insert(getResponse().length(), " 416 Range Not Satisfiable\n"));
	else if (statuCode == 417) setResponse(getResponse().insert(getResponse().length(), " 417 Expectation Failed\n"));
	else if (statuCode == 418) setResponse(getResponse().insert(getResponse().length(), " 418 I'm a teapot\n"));
	else if (statuCode == 422) setResponse(getResponse().insert(getResponse().length(), " 422 Unprocessable Entity\n"));
	else if (statuCode == 425) setResponse(getResponse().insert(getResponse().length(), " 425 Too Early\n"));
	else if (statuCode == 426) setResponse(getResponse().insert(getResponse().length(), " 426 Upgrade Required\n"));
	else if (statuCode == 428) setResponse(getResponse().insert(getResponse().length(), " 428 Precondition Required\n"));
	else if (statuCode == 429) setResponse(getResponse().insert(getResponse().length(), " 429 Too Many Requests\n"));
	else if (statuCode == 431) setResponse(getResponse().insert(getResponse().length(), " 431 Request Header Fields Too Large\n"));
	else if (statuCode == 451) setResponse(getResponse().insert(getResponse().length(), " 451 Unavailable For Legal Reasons\n"));
	else if (statuCode == 500) setResponse(getResponse().insert(getResponse().length(), " 500 Internal Server Error\n"));
	else if (statuCode == 501) setResponse(getResponse().insert(getResponse().length(), " 501 Not Implemented\n"));
	else if (statuCode == 502) setResponse(getResponse().insert(getResponse().length(), " 502 Bad Gateway\n"));
	else if (statuCode == 503) setResponse(getResponse().insert(getResponse().length(), " 503 Service Unavailable\n"));
	else if (statuCode == 504) setResponse(getResponse().insert(getResponse().length(), " 504 Gateway Timeout\n"));
	else if (statuCode == 505) setResponse(getResponse().insert(getResponse().length(), " 505 HTTP Version Not Supported\n"));
	else if (statuCode == 506) setResponse(getResponse().insert(getResponse().length(), " 506 Variant Also Negotiates\n"));
	else if (statuCode == 507) setResponse(getResponse().insert(getResponse().length(), " 507 Insufficient Sotrage\n"));
	else if (statuCode == 508) setResponse(getResponse().insert(getResponse().length(), " 508 Loop Detected\n"));
	else if (statuCode == 510) setResponse(getResponse().insert(getResponse().length(), " 510 Not Extended\n"));
	else if (statuCode == 511) setResponse(getResponse().insert(getResponse().length(), " 511 Network Authentication Required\n"));
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

int Response::statu_code(std::string path, std::vector<Routes> *routes, std::string method)
{
	struct stat	sb;
	if (stat(path.c_str(), &sb) == -1) return (404);
	if (routes && !method.empty())
	{
		int sep[2];
		sep[0] = path.find("www") + 3;
		sep[1] = path.rfind("/");
		std::string dir;
		if (sep[0] == sep[1]) dir = "/";
		else dir = path.substr(sep[0], sep[1] - (sep[0]));
		(void)routes;
	}
	return (200);
}

void Response::getMethod(std::string file, Server *serv, Request *req, int statuCode)
{
	std::string content;
	if (file[file.length() - 1] == '/') file.insert(file.length(), "index.html");
	std::string www = "./server/www";
	www.insert(www.length(), file);
	if (!statuCode) statuCode = statu_code(www, serv->_routes, "get");
	setFirstLine(statuCode);
	if (statuCode >= 400 && statuCode < 500) {
		char *statuChar = ft_itoa(statuCode);
		if (!statuChar) throw Response::BuildResponseException();
		www = serv->getErrorPage(statuChar);
		if (www.empty()) 
		{
			www = "./server/default/error";
			www.insert(www.length(), statuChar);
			www.insert(www.length(), ".html");
		}
		free(statuChar);
		if (statu_code(www, NULL, NULL) == 404) throw Response::BuildResponseException();
	}
	content = getContent(www);
	setDate();
	setLastModified(www);
	setLocation(file, statuCode);
	setRetryAfer(statuCode);
	setServer();
	setTransfetEncoding();
	setWWWAuthenticate(statuCode);
	setContentLanguage(req);
	setContentLength(content);
	setContentLocation(file);
	setContentType(www, req);
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
	struct timeval time;
	gettimeofday(&time, NULL);
	std::string request(req->getFirstLine()); // check si timeout pas de value
	int sep[2];
	sep[0] = request.find(' ');
	sep[1] = request.rfind(' ');
	std::string method = request.substr(0, sep[0]);
	std::string file = request.substr(sep[0] + 1, sep[1] - (sep[0] + 1));
	std::cout << "   \033[1;30mnew REQUEST: \033[0;33m " << method << " on " << file << "\033[0m" << std::endl;
	if (req->getTime() - time.tv_sec > 30){
		getMethod(file, serv, req, 408);
		throw "Timeout";
	}
	if (req->getHost().empty()) getMethod(file, serv, req, 400);
	else 
	{
		std::string host;
		std::string port("80");
		sep[0] = req->getHost().find(' ');
		sep[1] = req->getHost().rfind(':');
		if (sep[1] != -1) port = req->getHost().substr(sep[1] + 1);
		if (sep[1] == -1) sep[1] = req->getHost().length();
		host = req->getHost().substr(sep[0] + 1, sep[1] - (sep[0] + 1));
		if (!strcmp(host.c_str(), "localhost") || !strcmp(host.c_str(), "127.0.0.1"))
		{
			if (serv->getPort() != ft_atoi(port.c_str())) getMethod(file, serv, req, 400);
			else if (strcmp("localhost", serv->getHost().c_str()) && strcmp("127.0.0.1", serv->getHost().c_str())) getMethod(file, serv, req, 400);
		}
		else if (strcmp(host.c_str(), serv->getHost().c_str()) || serv->getPort() != ft_atoi(port.c_str())) getMethod(file, serv, req, 400);
		if (getResponse().empty())
		{
			if (!ft_strcmp(method.c_str(), "GET")) getMethod(file, serv, req, 0);
			else if (!ft_strcmp(method.c_str(), "HEAD")) head_method();
			else if (!ft_strcmp(method.c_str(), "PUT")) put_method();
			else if (!ft_strcmp(method.c_str(), "DELETE")) delete_method();
			else if (!ft_strcmp(method.c_str(), "CONNECT")) connect_method();
			else if (!ft_strcmp(method.c_str(), "OPTIONS")) options_method();
			else if (!ft_strcmp(method.c_str(), "TRACE")) trace_method();
		}
	}
	std::cout << "   \033[1;34mRESPONSE: \033[0;34m" << std::endl << "\033[0m{\033[3;36m" << getResponse() << "\033[0m}" << std::endl;

}

const char* Response::BuildResponseException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Building response failed\033[0m");
}