#include "../../includes/class/Response.hpp"
#include <iostream>
//#include <fstream>

Response::Response()
{

}

Response::Response(const Response &other)
{
	_response = other.getResponse();
	_file = other.getFile();
	_method = other.getMethod();
	_base = other.getBase();
	_www = other.getWww();
	_server = other.getServer();
	_status = other.getStatusCode();
	_routes = other._routes;
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

void Response::setFile(std::string value)
{
	this->_file = value;
}

std::string Response::getFile() const
{
	return(this->_file);
}

void Response::setMethod(std::string value)
{
	this->_method = value;
}

std::string Response::getMethod() const
{
	return(this->_method);
}

void Response::setBase(std::string value)
{
	this->_base = value;
}

std::string Response::getBase() const
{
	return(this->_base);
}

void Response::setWww(std::string value)
{
	this->_www = value;
}

std::string Response::getWww() const
{
	return(this->_www);
}

void Response::setServer(Server value)
{
	this->_server = value;
}

Server Response::getServer() const
{
	return(this->_server);
}

void Response::setStatusCode(int value)
{
	this->_status = value;
}

int Response::getStatusCode() const
{
	return(this->_status);
}

void Response::setRoutes(Routes value)
{
	this->_routes = value;
}

Routes Response::getRoutes() const
{
	return(this->_routes);
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

void Response::setContentLocation()
{
	setResponse(getResponse().insert(getResponse().length(), "Content-Location: "));
	setResponse(getResponse().insert(getResponse().length(), getFile()));
	setResponse(getResponse().insert(getResponse().length(), "\n"));
}

void Response::setContentType(Request *req)
{
	size_t nb = getWww().find_last_of(".");
	std::string type = getWww();
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
		std::string charset = req->getAcceptCharsets().substr(sep[0] + 2, sep[1] - (sep[0] + 1));
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

void Response::setLocation()
{
	if ((getStatusCode() >= 301 && getStatusCode() <= 308) || getStatusCode() == 201)
	{
		setResponse(getResponse().insert(getResponse().length(), "Location: "));
		setResponse(getResponse().insert(getResponse().length(), getFile()));
		setResponse(getResponse().insert(getResponse().length(), "\n"));
	}
}

void Response::setRetryAfer(Request *req)
{
	if (getStatusCode() == 503 || getStatusCode() == 429 || (getStatusCode() >= 300 && getStatusCode() <= 399))
	{
		setResponse(getResponse().insert(getResponse().length(), "Retry-After: "));
		setResponse(getResponse().insert(getResponse().length(), req->getDate()));
		setResponse(getResponse().insert(getResponse().length(), "\nRetry-After: 120\n"));
	}
}

void Response::setServerNginx()
{
	setResponse(getResponse().insert(getResponse().length(), "Server: Nginx\n"));
}

void Response::setWWWAuthenticate(Request *req)
{
	if (getStatusCode() == 401)
	{
		setResponse(getResponse().insert(getResponse().length(), "WWW-Authenticate: Basic realm=\"Access to the staging site\"\n"));
		if (!req->getAcceptCharsets().empty())
		{
			setResponse(getResponse().insert(getResponse().length() - 1, ", charset=\""));
			int sep[2];
			sep[0] = 15;
			sep[1] = req->getAcceptCharsets().find(',');
			if (sep[1] == -1) sep[1] = req->getAcceptCharsets().length();
			std::string charset = req->getAcceptCharsets().substr(sep[0] + 2, sep[1] - (sep[0] + 1));
			setResponse(getResponse().insert(getResponse().length() - 1, charset));
			setResponse(getResponse().insert(getResponse().length() - 1, "\""));
		}
	}
}

void Response::setConnectionClose()
{
	setResponse(getResponse().insert(getResponse().length(), "Connection: close\n"));
}

void Response::setFirstLine()
{
	setResponse("HTTP/1.1");
	if      (getStatusCode() == 100) setResponse(getResponse().insert(getResponse().length(), " 100 Continue\n"));
	else if (getStatusCode() == 101) setResponse(getResponse().insert(getResponse().length(), " 200 Switching Protocols\n"));
	else if (getStatusCode() == 103) setResponse(getResponse().insert(getResponse().length(), " 200 Ear;y Hints\n"));
	else if (getStatusCode() == 200) setResponse(getResponse().insert(getResponse().length(), " 200 OK\n"));
	else if (getStatusCode() == 201) setResponse(getResponse().insert(getResponse().length(), " 201 Created\n"));
	else if (getStatusCode() == 202) setResponse(getResponse().insert(getResponse().length(), " 202 Accepted\n"));
	else if (getStatusCode() == 203) setResponse(getResponse().insert(getResponse().length(), " 203 Non-Authoritative Information\n"));
	else if (getStatusCode() == 204) setResponse(getResponse().insert(getResponse().length(), " 204 No Content\n"));
	else if (getStatusCode() == 205) setResponse(getResponse().insert(getResponse().length(), " 205 Reset Content\n"));
	else if (getStatusCode() == 206) setResponse(getResponse().insert(getResponse().length(), " 206 Partial Content\n"));
	else if (getStatusCode() == 300) setResponse(getResponse().insert(getResponse().length(), " 300 Multiple Choices\n"));
	else if (getStatusCode() == 301) setResponse(getResponse().insert(getResponse().length(), " 301 Moved Permanently\n"));
	else if (getStatusCode() == 302) setResponse(getResponse().insert(getResponse().length(), " 302 Found\n"));
	else if (getStatusCode() == 303) setResponse(getResponse().insert(getResponse().length(), " 303 See Other\n"));
	else if (getStatusCode() == 304) setResponse(getResponse().insert(getResponse().length(), " 304 Not Modified\n"));
	else if (getStatusCode() == 307) setResponse(getResponse().insert(getResponse().length(), " 307 Temporary Redirect\n"));
	else if (getStatusCode() == 308) setResponse(getResponse().insert(getResponse().length(), " 308 Permanent Redirect\n"));
	else if (getStatusCode() == 400) setResponse(getResponse().insert(getResponse().length(), " 400 Bad Request\n"));
	else if (getStatusCode() == 401) setResponse(getResponse().insert(getResponse().length(), " 401 Unauthorized\n"));
	else if (getStatusCode() == 402) setResponse(getResponse().insert(getResponse().length(), " 402 Payment Required\n"));
	else if (getStatusCode() == 403) setResponse(getResponse().insert(getResponse().length(), " 403 Forbidden\n"));
	else if (getStatusCode() == 404) setResponse(getResponse().insert(getResponse().length(), " 404 Not Found\n"));
	else if (getStatusCode() == 405) setResponse(getResponse().insert(getResponse().length(), " 405 Method Not Allowed\n"));
	else if (getStatusCode() == 406) setResponse(getResponse().insert(getResponse().length(), " 406 Not Acceptable\n"));
	else if (getStatusCode() == 407) setResponse(getResponse().insert(getResponse().length(), " 407 Proxy Authentication Required\n"));
	else if (getStatusCode() == 408) setResponse(getResponse().insert(getResponse().length(), " 408 Request Timeout\n"));
	else if (getStatusCode() == 409) setResponse(getResponse().insert(getResponse().length(), " 409 Conflict\n"));
	else if (getStatusCode() == 410) setResponse(getResponse().insert(getResponse().length(), " 410 Gone\n"));
	else if (getStatusCode() == 411) setResponse(getResponse().insert(getResponse().length(), " 411 Length Required\n"));
	else if (getStatusCode() == 412) setResponse(getResponse().insert(getResponse().length(), " 412 Precondition Failed\n"));
	else if (getStatusCode() == 413) setResponse(getResponse().insert(getResponse().length(), " 413 Payload Too Large\n"));
	else if (getStatusCode() == 414) setResponse(getResponse().insert(getResponse().length(), " 414 URI Too Long\n"));
	else if (getStatusCode() == 415) setResponse(getResponse().insert(getResponse().length(), " 415 Unsupported Media Type\n"));
	else if (getStatusCode() == 416) setResponse(getResponse().insert(getResponse().length(), " 416 Range Not Satisfiable\n"));
	else if (getStatusCode() == 417) setResponse(getResponse().insert(getResponse().length(), " 417 Expectation Failed\n"));
	else if (getStatusCode() == 418) setResponse(getResponse().insert(getResponse().length(), " 418 I'm a teapot\n"));
	else if (getStatusCode() == 422) setResponse(getResponse().insert(getResponse().length(), " 422 Unprocessable Entity\n"));
	else if (getStatusCode() == 425) setResponse(getResponse().insert(getResponse().length(), " 425 Too Early\n"));
	else if (getStatusCode() == 426) setResponse(getResponse().insert(getResponse().length(), " 426 Upgrade Required\n"));
	else if (getStatusCode() == 428) setResponse(getResponse().insert(getResponse().length(), " 428 Precondition Required\n"));
	else if (getStatusCode() == 429) setResponse(getResponse().insert(getResponse().length(), " 429 Too Many Requests\n"));
	else if (getStatusCode() == 431) setResponse(getResponse().insert(getResponse().length(), " 431 Request Header Fields Too Large\n"));
	else if (getStatusCode() == 451) setResponse(getResponse().insert(getResponse().length(), " 451 Unavailable For Legal Reasons\n"));
	else if (getStatusCode() == 500) setResponse(getResponse().insert(getResponse().length(), " 500 Internal Server Error\n"));
	else if (getStatusCode() == 501) setResponse(getResponse().insert(getResponse().length(), " 501 Not Implemented\n"));
	else if (getStatusCode() == 502) setResponse(getResponse().insert(getResponse().length(), " 502 Bad Gateway\n"));
	else if (getStatusCode() == 503) setResponse(getResponse().insert(getResponse().length(), " 503 Service Unavailable\n"));
	else if (getStatusCode() == 504) setResponse(getResponse().insert(getResponse().length(), " 504 Gateway Timeout\n"));
	else if (getStatusCode() == 505) setResponse(getResponse().insert(getResponse().length(), " 505 HTTP Version Not Supported\n"));
	else if (getStatusCode() == 506) setResponse(getResponse().insert(getResponse().length(), " 506 Variant Also Negotiates\n"));
	else if (getStatusCode() == 507) setResponse(getResponse().insert(getResponse().length(), " 507 Insufficient Sotrage\n"));
	else if (getStatusCode() == 508) setResponse(getResponse().insert(getResponse().length(), " 508 Loop Detected\n"));
	else if (getStatusCode() == 510) setResponse(getResponse().insert(getResponse().length(), " 510 Not Extended\n"));
	else if (getStatusCode() == 511) setResponse(getResponse().insert(getResponse().length(), " 511 Network Authentication Required\n"));
}

std::string Response::getContent(std::string path)
{
	std::string ret;

	int fd;
	int res;
	if ((fd = open(path.c_str(), O_RDONLY)) < 0) throw Response::BuildResponseException();
	char line[1];
	while ((res = read(fd, line, 1)) == 1)
		ret.insert(ret.length(), line, 1);
	close(fd);
	return (ret);
}

void Response::print_directory(const char *path)
{
	DIR *d = opendir(path);
	size_t path_len = ft_strlen(path);

	if (d)
	{
		struct dirent *p;

		while ((p=readdir(d)))
		{
			std::string buf;
			size_t len;

			/* Skip the names "." and ".." as we don't want to recurse on them. */
			if (!ft_strcmp(p->d_name, ".") || !ft_strcmp(p->d_name, ".."))
				continue;

			len = path_len + ft_strlen(p->d_name) + 2;
			struct stat statbuf;
			buf = path;
			buf.push_back('/');
			buf.insert(buf.length(), p->d_name);
			if (!stat(buf.c_str(), &statbuf)) 
			{
				if (S_ISDIR(statbuf.st_mode))
					std::cout << buf << "/\n";
				else
					std::cout << buf << "\n";
				continue;
			}
		}
		closedir(d);
	}
}

int Response::check_exist(std::string path)
{
	struct stat	sb;
	if (stat(path.c_str(), &sb) == -1) return (-1);
	return (0);
}

int Response::statu_code(std::string path)
{
	struct stat	sb;
	if (stat(path.c_str(), &sb) == -1) return (404);
	for (std::list<std::string>::iterator it = getRoutes()._http_method.begin() ; it != getRoutes()._http_method.end(); ++it)
    {
		if (!ft_strncmp(it->c_str(), getMethod().c_str(), 3))
			return (200);
		if (it->empty())
			return (405);
	}
	return (405);
}

void Response::getMethod(Request *req)
{
	head_method(req);
	setResponse(getResponse().insert(getResponse().length(), getContent(getWww())));
}

void Response::head_method(Request *req)
{

	setFirstLine();
	if (getStatusCode() >= 400 && getStatusCode() < 500) {
		char *statuChar = ft_itoa(getStatusCode());
		if (!statuChar) throw Response::BuildResponseException();
		setWww(getServer().getErrorPage(statuChar));
		if (getWww().empty())
		{
			setWww("./server/default/error");
			setWww(getWww().insert(getWww().length(), statuChar));
			setWww(getWww().insert(getWww().length(), ".html"));
		}
		free(statuChar);
		if (check_exist(getWww())) throw Response::BuildResponseException();
	}
	setDate();
	setLastModified(getWww());
	setLocation();
	setRetryAfer(req);
	setServerNginx();
	setWWWAuthenticate(req);
	setContentLanguage(req);
	setContentLength(getContent(getWww()));
	setContentLocation();
	setContentType(req);
	setConnectionClose();
	setResponse(getResponse().insert(getResponse().length(), "\n"));
}

void Response::post_method()
{
	;
}

void Response::put_method()
{
	;
}

void Response::delete_method()
{
	setFirstLine();
	if (getStatusCode() >= 400 && getStatusCode() < 500) {
		char *statuChar = ft_itoa(getStatusCode());
		if (!statuChar) throw Response::BuildResponseException();
		setWww(getServer().getErrorPage(statuChar));
		if (getWww().empty())
		{
			setWww("./server/default/error");
			setWww(getWww().insert(getWww().length(), statuChar));
			setWww(getWww().insert(getWww().length(), ".html"));
		}
		free(statuChar);
		if (check_exist(getWww())) throw Response::BuildResponseException();
	}
	if (unlink(getWww().c_str()))
		write(1, strerror(errno), ft_strlen(strerror(errno)));
}

void Response::connect_method()
{
	// https://stackoverflow.com/questions/43264266/c-socket-send-and-connect
	//	int server_fd, opt = 1;
	//if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) exit_err("socket failed", NULL, -1, -1);
	//if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) exit_err("setsockopt failed", NULL, -1, server_fd);
	//struct sockaddr_in address;
	//address.sin_family = AF_INET;
	//if (ft_strcmp(serv.getHost().c_str(), "localhost"))
	//	address.sin_addr.s_addr = inet_addr(serv.getHost().c_str());
	//else
	//	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	//address.sin_port = htons( serv.getPort() );
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
	std::string request(req->getFirstLine());
	int sep[2];
	if (!request.empty())
	{
		sep[0] = request.find(' ');
		sep[1] = request.rfind(' ');
		setMethod(request.substr(0, sep[0]));
		setFile(request.substr(sep[0] + 1, sep[1] - (sep[0] + 1)));
		this->setRoutes(serv->getRoute(getFile()));
		setServer(*serv);
		setBase(getRoutes().getLocation());
		if (getFile()[getFile().length() - 1] == '/') setFile(getFile().insert(getFile().length(), "index.html"));
		setWww(getBase());
		setWww(getBase().insert(getBase().length(), getFile()));
		std::cout << "   \033[1;30mnew REQUEST: \033[0;33m " << getMethod() << " on " << getFile() << "\033[0m" << std::endl;
	};
	if (time.tv_sec - req->getTime() < TIMEOUT){
		setFile("error408.html");
		setStatusCode(408);
		getMethod(req);
	}
	else {	
		setStatusCode(400);
		if (req->getHost().empty()) {
				getMethod(req);
		}
		else 
		{
			std::string host;
			std::string port("80");
			sep[0] = req->getHost().find(' ');
			sep[1] = req->getHost().rfind(':');
			if (sep[1] != -1) port = req->getHost().substr(sep[1] + 1);
			if (sep[1] == -1) sep[1] = req->getHost().length();
			host = req->getHost().substr(sep[0] + 1, sep[1] - (sep[0] + 1));
			if (!ft_strcmp(host.c_str(), "localhost") || !ft_strcmp(host.c_str(), "127.0.0.1"))
			{
				if (getServer().getPort() != ft_atoi(port.c_str())) getMethod(req);
				else if (ft_strcmp("localhost", getServer().getHost().c_str()) && ft_strcmp("127.0.0.1", getServer().getHost().c_str())) getMethod(req);
			}
			else if (ft_strcmp(host.c_str(), getServer().getHost().c_str()) || getServer().getPort() != ft_atoi(port.c_str())) getMethod(req);
			if (getResponse().empty())
			{
				setStatusCode(statu_code(getWww()));
				if (!ft_strcmp(getMethod().c_str(), "GET")) getMethod(req);
				else if (!ft_strcmp(getMethod().c_str(), "HEAD")) head_method(req);
				else if (!ft_strcmp(getMethod().c_str(), "PUT")) put_method();
				else if (!ft_strcmp(getMethod().c_str(), "DELETE")) delete_method();
				else if (!ft_strcmp(getMethod().c_str(), "CONNECT")) connect_method();
				else if (!ft_strcmp(getMethod().c_str(), "OPTIONS")) options_method();
				else if (!ft_strcmp(getMethod().c_str(), "TRACE")) trace_method();
			}
		}
	}
	std::cout << "   \033[1;34mRESPONSE: \033[0;34m" << std::endl << "\033[0m" << getResponse() << std::endl;

}

const char* Response::BuildResponseException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Building response failed\033[0m");
}