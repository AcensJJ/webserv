#include "../../includes/class/Response.hpp"
#include <iostream>

Response::Response()
{
	Client **allclient = new (Client (*[FD_SETSIZE]) );
	for (int i = 1; i < FD_SETSIZE; i++)
		allclient[i] = NULL;
	setClient(allclient);
}

Response::Response(const Response &other)
{
	_file = other.getFile();
	_method = other.getMethod();
	_base = other.getBase();
	_www = other.getWww();
	_listingContent = other.getListingContent();
	if (getServer()) delete getServer();
	Server *serv = new Server(*other.getServer());
	_server = serv;
	_routes = other.getRoutes();
	_status = other.getStatusCode();
	_allclient = other.getClient();
	_req = other.getRequest();
	_url = other.getUrl();
	_i = other.getI();
	configMethod();
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

void Response::setUrl(std::string value)
{
	this->_url = value;
}

std::string Response::getUrl() const
{
	return(this->_url);
}

void Response::setServer(Server* value)
{
	this->_server = value;
}

Server* Response::getServer() const
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

void Response::setI(int value)
{
	this->_i = value;
}

int Response::getI() const
{
	return(this->_i);
}

void Response::setRoutes(Routes value)
{
	this->_routes = value;
}

Routes Response::getRoutes() const
{
	return(this->_routes);
}

void Response::setListingContent(std::string value)
{
	this->_listingContent = value;
}

std::string Response::getListingContent() const
{
	return(this->_listingContent);
}

void		Response::setRequest(Request* value)
{
	this->_req = value;
}

Request*		Response::getRequest() const
{
	return (this->_req);
}

void Response::setClient(Client** value)
{
	this->_allclient = value;
}

Client** Response::getClient() const
{
	return (this->_allclient);
}

void Response::configDefault()
{
	std::map<std::string, std::string> mymap;
	std::string str = getRoutes().getDefault();
	int sep;
	int i = 0;
	while (!i)
	{
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			i++;
		str = &str[i];
		i = 0;
		sep = str.find(' ');
		if (sep == -1) {
			sep = str.length();
			i = -1;
		}
		std::string tmp = str.substr(0 , sep);
		mymap.insert(std::pair<std::string, std::string>(tmp, tmp));
		str = &str[sep + 1];
	}
	_default = mymap;
}

void Response::configMethod()
{
	std::map<std::string, std::string> mymap;

	int i = 0;
	std::string str = getRoutes().getMethod();
	while (str[i])
	{
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			i++;
		std::string method;
		if (!ft_strncmp(&str[i], "GET", 3)) {
			mymap.insert(std::pair<std::string, std::string>("GET", "GET"));
			i += 3;	
		}
		else if (!ft_strncmp(&str[i], "HEAD", 4)) {
			mymap.insert(std::pair<std::string, std::string>("HEAD", "HEAD"));
			i += 4;
		}
		else if (!ft_strncmp(&str[i], "POST", 4)) {
			mymap.insert(std::pair<std::string, std::string>("POST", "POST"));
			i += 4;
		}
		else if (!ft_strncmp(&str[i], "PUT", 3)) {
			mymap.insert(std::pair<std::string, std::string>("PUT", "PUT"));
			i += 3;
		}
		else if (!ft_strncmp(&str[i], "DELETE", 6)) {
			mymap.insert(std::pair<std::string, std::string>("DELETE", "DELETE"));
			i += 6;
		}
		else if (!ft_strncmp(&str[i], "CONNECT", 7)) {
			mymap.insert(std::pair<std::string, std::string>("CONNECT", "CONNECT"));
			i += 7;
		}
		else if (!ft_strncmp(&str[i], "TRACE", 5)) {
			mymap.insert(std::pair<std::string, std::string>("TRACE", "TRACE"));
			i += 5;
		}
		else if (!ft_strncmp(&str[i], "PATCH", 5)) {
			mymap.insert(std::pair<std::string, std::string>("PATCH", "PATCH"));
			i += 5;
		}
		_http_method = mymap;
		i++;
	}
	
}

void Response::setDate()
{
	char *buf;
	struct timeval tv;
	time_t curtime;

	if (!(buf = (char *)malloc(30))) throw Response::BuildResponseException();
	ft_bzero(buf, 30);
	gettimeofday(&tv, NULL); 
	curtime=tv.tv_sec;
	getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Date: "));
	strftime(buf, sizeof(buf),"%a, %d %b %Y %H:%M:%S GMT", localtime(&curtime));
	getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), buf));
	getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "\n"));
	delete buf;
}

void Response::setAllow()
{
	if (getStatusCode() == 405)
	{
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Allow:"));
		for (std::map<std::string, std::string>::iterator it = _http_method.begin() ; it != _http_method.end(); ++it)
		{
			if (it != _http_method.begin()) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), ", "));
			else getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " "));
			getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), it->second));
		}
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "\n"));
	}
}

void Response::setContentLanguage()
{
	if (!getRequest()->getAcceptLanguage().empty())
	{
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Langage: "));
		int sep[2];
		sep[0] = 16;
		sep[1] = getRequest()->getAcceptLanguage().find(',');
		if (sep[1] == -1) sep[1] = getRequest()->getAcceptLanguage().length();
		std::string language = getRequest()->getAcceptLanguage().substr(sep[0] + 1, sep[1] - (sep[0] + 1));
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), language + "\n"));
	}
}

void Response::setContentLength(std::string content)
{
	char* len;
	int size = 0;
	size = content.length();
	if (!(len = ft_itoa(size))) throw Response::BuildResponseException();
	getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Length: "));
	getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), len));
	getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "\n"));
	free(len);
}

void Response::setContentLocation()
{
	getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Location: " + getUrl() + "\n"));
}

void Response::setContentType()
{
	size_t nb = getWww().find_last_of(".");
	std::string type = getWww();
	type.erase(0, nb);
	if (!ft_strcmp(type.c_str() , ".aac"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: audio/aac\n"));
	if (!ft_strcmp(type.c_str() , ".abw"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/x-abiword\n"));
	if (!ft_strcmp(type.c_str() , ".arc"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/octet-stream\n"));
	if (!ft_strcmp(type.c_str() , ".avi"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: video/x-msvideo\n"));
	if (!ft_strcmp(type.c_str() , ".azw"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/vnd.amazon.ebook\n"));
	if (!ft_strcmp(type.c_str() , ".bin"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/octet-stream\n"));
	if (!ft_strcmp(type.c_str() , ".bmp"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: image/bmp\n"));
	if (!ft_strcmp(type.c_str() , ".bz"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/x-bzip\n"));
	if (!ft_strcmp(type.c_str() , ".bz2"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/x-bzip2\n"));
	if (!ft_strcmp(type.c_str() , ".csh"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/x-csh\n"));
	if (!ft_strcmp(type.c_str() , ".css"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: text/css\n"));
	if (!ft_strcmp(type.c_str() , ".csv"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: text/csv\n"));
	if (!ft_strcmp(type.c_str() , ".doc"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/msword\n"));
	if (!ft_strcmp(type.c_str() , ".docx"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: pplication/vnd.openxmlformats-officedocument.wordprocessingml.document\n"));
	if (!ft_strcmp(type.c_str() , ".eot"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/vnd.ms-fontobject\n"));
	if (!ft_strcmp(type.c_str() , ".epub"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/epub+zip\n"));
	if (!ft_strcmp(type.c_str() , ".gif"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: image/gif\n"));
	if (!ft_strcmp(type.c_str() , ".htm"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: text/html\n"));
	if (!ft_strcmp(type.c_str() , ".html"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: text/html\n"));
	if (!ft_strcmp(type.c_str() , ".ico"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: image/x-icon\n"));
	if (!ft_strcmp(type.c_str() , ".ics"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: text/calendar\n"));
	if (!ft_strcmp(type.c_str() , ".jar"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/java-archive\n"));
	if (!ft_strcmp(type.c_str() , ".jpg"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: image/jpeg\n"));
	if (!ft_strcmp(type.c_str() , ".jpeg"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: image/jpeg\n"));
	if (!ft_strcmp(type.c_str() , ".js"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/javascript\n"));
	if (!ft_strcmp(type.c_str() , ".json"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/json\n"));
	if (!ft_strcmp(type.c_str() , ".mid"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: audio/midi\n"));
	if (!ft_strcmp(type.c_str() , ".midi"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: audio/midi\n"));
	if (!ft_strcmp(type.c_str() , ".mpeg"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: video/mpeg\n"));
	if (!ft_strcmp(type.c_str() , ".mpkg"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/vnd.apple.installer+xml\n"));
	if (!ft_strcmp(type.c_str() , ".odp"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/vnd.oasis.opendocument.presentation\n"));
	if (!ft_strcmp(type.c_str() , ".ods"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/vnd.oasis.opendocument.spreadsheet\n"));
	if (!ft_strcmp(type.c_str() , ".odt"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/vnd.oasis.opendocument.text\n"));
	if (!ft_strcmp(type.c_str() , ".oga"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: audio/ogg\n"));
	if (!ft_strcmp(type.c_str() , ".ogv"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: video/ogg\n"));
	if (!ft_strcmp(type.c_str() , ".ogx"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/ogg\n"));
	if (!ft_strcmp(type.c_str() , ".otf"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: font/otf\n"));
	if (!ft_strcmp(type.c_str() , ".png"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: image/png\n"));
	if (!ft_strcmp(type.c_str() , ".pdf"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/pdf\n"));
	if (!ft_strcmp(type.c_str() , ".ppt"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/vnd.ms-powerpoint\n"));
	if (!ft_strcmp(type.c_str() , ".pptx"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/vnd.openxmlformats-officedocument.presentationml.presentation\n"));
	if (!ft_strcmp(type.c_str() , ".rar"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/x-rar-compressed\n"));
	if (!ft_strcmp(type.c_str() , ".rtf"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/rtf\n"));
	if (!ft_strcmp(type.c_str() , ".sh"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/x-sh\n"));
	if (!ft_strcmp(type.c_str() , ".svg"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: image/svg+xml\n"));
	if (!ft_strcmp(type.c_str() , ".swf"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/x-shockwave-flash\n"));
	if (!ft_strcmp(type.c_str() , ".tar"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/x-tar\n"));
	if (!ft_strcmp(type.c_str() , ".tif"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: image/tiff\n"));
	if (!ft_strcmp(type.c_str() , ".tiff"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: image/tiff\n"));
	if (!ft_strcmp(type.c_str() , ".ts"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/typescript\n"));
	if (!ft_strcmp(type.c_str() , ".ttf"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: font/ttf\n"));
	if (!ft_strcmp(type.c_str() , ".vsd"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/vnd.visio\n"));
	if (!ft_strcmp(type.c_str() , ".wav"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: audio/x-wav\n"));
	if (!ft_strcmp(type.c_str() , ".weba"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: audio/webm\n"));
	if (!ft_strcmp(type.c_str() , ".webm"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: video/webm\n"));
	if (!ft_strcmp(type.c_str() , ".webp"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: image/webp\n"));
	if (!ft_strcmp(type.c_str() , ".woff"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: font/woff\n"));
	if (!ft_strcmp(type.c_str() , ".woff2")) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: font/woff2\n"));
	if (!ft_strcmp(type.c_str() , ".xhtml")) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/xhtml+xml\n"));
	if (!ft_strcmp(type.c_str() , ".xls"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/vnd.ms-excel\n"));
	if (!ft_strcmp(type.c_str() , ".xlsx"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet\n"));
	if (!ft_strcmp(type.c_str() , ".xml"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/xml\n"));
	if (!ft_strcmp(type.c_str() , ".xul"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/vnd.mozilla.xul+xml\n"));
	if (!ft_strcmp(type.c_str() , ".zip"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/zip\n"));
	if (!ft_strcmp(type.c_str() , ".3gp"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: video/3gpp\n"));
	if (!ft_strcmp(type.c_str() , ".3g2"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: video/3gpp2\n"));
	if (!ft_strcmp(type.c_str() , ".7z"))	 getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Content-Type: application/x-7z-compressed\n"));
	if (!getRequest()->getAcceptCharsets().empty())
	{
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length() - 1, "; charset="));
		int sep[2];
		sep[0] = 15;
		sep[1] = getRequest()->getAcceptCharsets().find(',');
		if (sep[1] == -1) sep[1] = getRequest()->getAcceptCharsets().length();
		std::string charset = getRequest()->getAcceptCharsets().substr(sep[0] + 2, sep[1] - (sep[0] + 1));
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length() - 1, charset));
	}
}

void Response::setLastModified(std::string path)
{
	struct stat	sb;
	if (stat(path.c_str(), &sb) >= 0)
	{
		char *date;
		if (!(date = (char *)malloc(12))) throw Response::BuildResponseException();
		ft_bzero(date, 12);
		strftime(date, 3, "%a", gmtime(&(sb.st_ctime)));
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Last-Modified: "));
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), date));
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), ", "));
		ft_bzero(date, 3);
		strftime(date, 11, "%d %h %Y", gmtime(&(sb.st_ctime)));
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), date));
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " "));
		ft_bzero(date, 11);
		strftime(date, 8, "%H:%M:%S", gmtime(&(sb.st_ctime)));
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), date));
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " GMT"));
		free(date);
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "\n"));
	}
}

void Response::setLocation()
{
	if ((getStatusCode() >= 301 && getStatusCode() <= 308) || getStatusCode() == 201)
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Location: " + getFile() + "\n"));
}

void Response::setRetryAfer()
{
	if (getStatusCode() == 503 || getStatusCode() == 429 || (getStatusCode() >= 300 && getStatusCode() <= 399))
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Retry-After: " + getRequest()->getDate() + "\nRetry-After: 120\n"));
}

void Response::setServerNginx()
{
	getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Server: Nginx\n"));
}

void Response::setWWWAuthenticate()
{
	if (getStatusCode() == 401)
	{
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "WWW-Authenticate: Basic realm=\"Access to the staging site\"\n"));
		if (!getRequest()->getAcceptCharsets().empty())
		{
			getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length() - 1, ", charset=\""));
			int sep[2];
			sep[0] = 15;
			sep[1] = getRequest()->getAcceptCharsets().find(',');
			if (sep[1] == -1) sep[1] = getRequest()->getAcceptCharsets().length();
			std::string charset = getRequest()->getAcceptCharsets().substr(sep[0] + 2, sep[1] - (sep[0] + 1));
			getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length() - 1, charset + "\""));
		}
	}
}

void Response::setConnectionClose()
{
	getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "Connection: close\n"));
}

void Response::setFirstLine()
{
	getClient()[getI()]->setResponse("HTTP/1.1");
	if      (getStatusCode() == 100) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 100 Continue\n"));
	else if (getStatusCode() == 101) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 101 Switching Protocols\n"));
	else if (getStatusCode() == 103) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 103 Early Hints\n"));
	else if (getStatusCode() == 200) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 200 OK\n"));
	else if (getStatusCode() == 201) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 201 Created\n"));
	else if (getStatusCode() == 202) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 202 Accepted\n"));
	else if (getStatusCode() == 203) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 203 Non-Authoritative Information\n"));
	else if (getStatusCode() == 204) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 204 No Content\n"));
	else if (getStatusCode() == 205) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 205 Reset Content\n"));
	else if (getStatusCode() == 206) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 206 Partial Content\n"));
	else if (getStatusCode() == 300) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 300 Multiple Choices\n"));
	else if (getStatusCode() == 301) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 301 Moved Permanently\n"));
	else if (getStatusCode() == 302) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 302 Found\n"));
	else if (getStatusCode() == 303) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 303 See Other\n"));
	else if (getStatusCode() == 304) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 304 Not Modified\n"));
	else if (getStatusCode() == 307) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 307 Temporary Redirect\n"));
	else if (getStatusCode() == 308) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 308 Permanent Redirect\n"));
	else if (getStatusCode() == 400) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 400 Bad Request\n"));
	else if (getStatusCode() == 401) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 401 Unauthorized\n"));
	else if (getStatusCode() == 402) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 402 Payment Required\n"));
	else if (getStatusCode() == 403) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 403 Forbidden\n"));
	else if (getStatusCode() == 404) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 404 Not Found\n"));
	else if (getStatusCode() == 405) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 405 Method Not Allowed\n"));
	else if (getStatusCode() == 406) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 406 Not Acceptable\n"));
	else if (getStatusCode() == 407) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 407 Proxy Authentication Required\n"));
	else if (getStatusCode() == 408) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 408 Request Timeout\n"));
	else if (getStatusCode() == 409) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 409 Conflict\n"));
	else if (getStatusCode() == 410) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 410 Gone\n"));
	else if (getStatusCode() == 411) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 411 Length Required\n"));
	else if (getStatusCode() == 412) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 412 Precondition Failed\n"));
	else if (getStatusCode() == 413) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 413 Payload Too Large\n"));
	else if (getStatusCode() == 414) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 414 URI Too Long\n"));
	else if (getStatusCode() == 415) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 415 Unsupported Media Type\n"));
	else if (getStatusCode() == 416) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 416 Range Not Satisfiable\n"));
	else if (getStatusCode() == 417) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 417 Expectation Failed\n"));
	else if (getStatusCode() == 418) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 418 I'm a teapot\n"));
	else if (getStatusCode() == 422) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 422 Unprocessable Entity\n"));
	else if (getStatusCode() == 425) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 425 Too Early\n"));
	else if (getStatusCode() == 426) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 426 Upgrade Required\n"));
	else if (getStatusCode() == 428) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 428 Precondition Required\n"));
	else if (getStatusCode() == 429) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 429 Too Many Requests\n"));
	else if (getStatusCode() == 431) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 431 Request Header Fields Too Large\n"));
	else if (getStatusCode() == 451) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 451 Unavailable For Legal Reasons\n"));
	else if (getStatusCode() == 500) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 500 Internal Server Error\n"));
	else if (getStatusCode() == 501) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 501 Not Implemented\n"));
	else if (getStatusCode() == 502) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 502 Bad Gateway\n"));
	else if (getStatusCode() == 503) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 503 Service Unavailable\n"));
	else if (getStatusCode() == 504) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 504 Gateway Timeout\n"));
	else if (getStatusCode() == 505) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 505 HTTP Version Not Supported\n"));
	else if (getStatusCode() == 506) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 506 Variant Also Negotiates\n"));
	else if (getStatusCode() == 507) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 507 Insufficient Sotrage\n"));
	else if (getStatusCode() == 508) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 508 Loop Detected\n"));
	else if (getStatusCode() == 510) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 510 Not Extended\n"));
	else if (getStatusCode() == 511) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), " 511 Network Authentication Required\n"));
}

std::string Response::getContent(std::string path)
{
	if (_cgi.getDo()) return (_cgi.getBody());
	if (getClient()[getI()]->getBodyToWork() && getStatusCode() >= 200 && getStatusCode() <= 299){
		if (getClient()[getI()]->_chunck.size() > 0) getClient()[getI()]->setMsg("");
		for (std::list<std::string>::iterator itr = getClient()[getI()]->_chunck.begin(); itr != getClient()[getI()]->_chunck.end(); itr++)
			getClient()[getI()]->setMsg(getClient()[getI()]->getMsg() + *itr);
			return (getClient()[getI()]->getMsg());
	}
	std::string ret;
	if (!getListingContent().empty() && getStatusCode() >= 200 && getStatusCode() < 300 ) return (getListingContent());
	int fd;
	int res;
	if ((fd = open(path.c_str(), O_RDONLY)) < 0) throw Response::BuildResponseException();
	char line[1];
	while ((res = read(fd, line, 1)) == 1)
		ret.insert(ret.length(), line, 1);
	close(fd);
	return (ret);
}

int Response::print_directory(const char *path)
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
				buf = buf.erase(0, getWww().length() + 1);
				if (S_ISDIR(statbuf.st_mode)) {
					buf.insert(buf.length(), "/");
				}
				setListingContent(getListingContent().insert(getListingContent().length(), "<li><a href=\"" + buf + "\">" + buf + "</a></li>\n"));
				continue;
			}
		}
		closedir(d);
		return (0);
	}
	return (-1);
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
	if (_http_method.find(getMethod()) != _http_method.end()) {
		if (S_ISDIR(sb.st_mode)) return (404);
		return (200);
	}
	return (405);
}

void Response::setAllHeader()
{
	if ((getStatusCode() >= 200 && getStatusCode() <= 299) && !getRoutes().getLimitClientBody().empty() && (int)getContent(getWww()).length() > ft_atoi(getRoutes().getLimitClientBody().c_str()))
	{
		_cgi.setBody("");
		getClient()[getI()]->setBodyToWork(false);
		setListingContent("");
		getClient()[getI()]->setResponse("");
		setStatusCode(413);
		check_method();
	}
	else {
		std::string content = getWww();
		setDate();
		setLastModified(content);
		setLocation();
		setRetryAfer();
		setServerNginx();
		setWWWAuthenticate();
		setAllow();
		setContentLanguage();
		setContentLength(getContent(content));
		setContentLocation();
		setContentType();
		setConnectionClose();
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "\n"));
	}
}

void Response::get_method()
{
	head_method();
	getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), getContent(getWww())));
}

void Response::head_method()
{
	setFirstLine();
	if (getStatusCode() >= 400 && getStatusCode() < 500) {
		char *statuChar = ft_itoa(getStatusCode());
		if (!statuChar) throw Response::BuildResponseException();
		setWww(getServer()->getErrorPage(statuChar));
		if (getWww().empty())
		{
			setWww("./server/default/error");
			setWww(getWww().insert(getWww().length(), statuChar));
			setWww(getWww().insert(getWww().length(), ".html"));
		}
		free(statuChar);
		if (check_exist(getWww())) throw Response::BuildResponseException();
	}
	setAllHeader();
	if (!ft_strcmp("HEAD", getMethod().c_str())) getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "\n"));
}

void Response::post_method()
{
	put_method();
}

void Response::put_method()
{
	int ret(0), fd(0);
	if (getStatusCode() >= 400 && getStatusCode() < 500 && getStatusCode() != 404) {
		char *statuChar = ft_itoa(getStatusCode());
		if (!statuChar) throw Response::BuildResponseException();
		setWww(getServer()->getErrorPage(statuChar));
		if (getWww().empty())
		{
			setWww("./server/default/error");
			setWww(getWww().insert(getWww().length(), statuChar));
			setWww(getWww().insert(getWww().length(), ".html"));
		}
		free(statuChar);
		if (check_exist(getWww())) throw Response::BuildResponseException();
		setFirstLine();
		setAllHeader();
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), getContent(getWww())));
	}
	else
	{
		ret = unlink(getWww().c_str());
		if (ret == -1) setStatusCode(201);
		fd = open(getWww().c_str(), O_CREAT | O_WRONLY, 0644);
		if (fd == -1) throw Response::BuildResponseException();
		std::string content = getContent(getWww());
		write(fd, content.c_str(), content.length());
		close(fd);
		if (getStatusCode() != 201 && content.empty()) setStatusCode(204);
		setFirstLine();
		setContentLocation();
		if (!(ft_strcmp(getMethod().c_str(), "POST"))) setAllHeader();
		else getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), "\n"));
		getClient()[getI()]->setResponse(getClient()[getI()]->getResponse().insert(getClient()[getI()]->getResponse().length(), content));
	}
}

void Response::delete_method()
{
	int ret = 0;
	setFirstLine();
	if (getStatusCode() >= 400 && getStatusCode() < 500) {
		char *statuChar = ft_itoa(getStatusCode());
		if (!statuChar) throw Response::BuildResponseException();
		setWww(getServer()->getErrorPage(statuChar));
		if (getWww().empty())
		{
			setWww("./server/default/error");
			setWww(getWww().insert(getWww().length(), statuChar));
			setWww(getWww().insert(getWww().length(), ".html"));
		}
		free(statuChar);
		if (check_exist(getWww())) throw Response::BuildResponseException();
	}
	else if ((!(ret = unlink(getWww().c_str()))))
	{
		setWww("./server/default/delete.html");
		if (check_exist(getWww())) throw Response::BuildResponseException();
		get_method();
	}
	if (ret == -1)
		write(1, strerror(errno), ft_strlen(strerror(errno)));
}

void Response::check_method()
{
	if (!ft_strcmp(getMethod().c_str(), "GET")) get_method();
	else if (!ft_strcmp(getMethod().c_str(), "HEAD")) head_method();
	else if (!ft_strcmp(getMethod().c_str(), "PUT")) put_method();
	else if (!ft_strcmp(getMethod().c_str(), "POST")) post_method();
	else if (!ft_strcmp(getMethod().c_str(), "DELETE")) delete_method();
}

void Response::config_response(char **env, int i)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	setI(i);
	_cgi.setDo(false);
	std::string request(getRequest()->getFirstLine());
	size_t sep[2];
	if (!request.empty())
	{
		sep[0] = request.find(' ');
		sep[1] = request.rfind(' ');
		setMethod(request.substr(0, sep[0]));
		setUrl(request.substr(sep[0] + 1, sep[1] - (sep[0] + 1)));
		setFile(getUrl());
		std::cout << std::endl << "   \033[1;30mnew REQUEST: \033[0;33m " << getMethod() << " on " << getFile() << "\033[0m" << std::endl;            
		this->setRoutes(getServer()->getRoute(getFile(), 0));
		configMethod();
		setBase(getRoutes().getLocation());
		if (getBase().empty()) setBase(SERV_WWW);
		if (getRoutes().getDirFile().rfind("/ *.") == std::string::npos && getRoutes().getDirFile().rfind('/') != std::string::npos) setFile(&getFile()[getRoutes().getDirFile().rfind('/') + 1]);
		if (getFile()[0] == '/') setFile(&getFile()[1]);
		setWww(getBase());
		this->setRoutes(getServer()->getRoute(getUrl(), 1));
		setStatusCode(0);
	}
	if (time.tv_sec - getRequest()->getTime() > TIMEOUT)
		setStatusCode(408);
	 else {
        if (!getStatusCode())
        {
			struct stat	sb;
			if (stat(getWww().insert(getWww().length(), getFile()).c_str(), &sb) != -1) if (S_ISDIR(sb.st_mode) && !S_ISREG(sb.st_mode)) {
				setFile(getFile().insert(getFile().length(), "/"));
			}
			if (!getRoutes().getListen() && (getFile()[getFile().length() - 1] == '/' || getFile().empty()) && !ft_strcmp("GET", getMethod().c_str()))
            {
                configDefault();
                setStatusCode(404);
                for (std::map<std::string, std::string>::iterator it = _default.begin() ; it != _default.end() && getStatusCode() == 404; ++it)
                {
                    std::string tmp = getFile();
                    if (!check_exist(getWww().insert(getWww().length(), tmp + it->second)))
                    {
                        setFile(tmp + it->second);
                		setWww(getBase().insert(getBase().length(), getFile()));
                        setStatusCode(statu_code(getWww()));
                    }
                }
            }
            else if (_http_method.find(getMethod()) != _http_method.end() && getRoutes().getListen() && (getFile()[getFile().length() - 1] == '/' || getFile().empty()) && !ft_strcmp("GET", getMethod().c_str()))
            {
                setWww(getBase().insert(getBase().length(), getFile()));
                setListingContent("<H1>Auto-index</H1>\n\n");
                if (!getStatusCode()) setStatusCode(statu_code(getWww()));
                if (print_directory(getWww().c_str())) {
                    setListingContent("");
                    setStatusCode(404);
        		}
				struct stat	sb;
				if (stat(getWww().c_str(), &sb) != -1) if (S_ISDIR(sb.st_mode)) setStatusCode (200);
			}
            else {
                setWww(getBase().insert(getBase().length(), getFile()));
                if (!getStatusCode()) setStatusCode(statu_code(getWww()));
            }
            if (_http_method.find(getMethod()) != _http_method.end() && ((!getRoutes().getCGIPath().empty()) && (getMethod() == "GET" || getMethod() == "POST" || getMethod() == "PUT" )))
            {
				_cgi.setEnv(env);
				_cgi.setRoutes(getRoutes());
				_cgi.setServer(getServer());
				_cgi.setMethod(getMethod());
				_cgi.setFile(getUrl());
				_cgi.setClient(getClient()[i]);
				_cgi.setRequest(getRequest());
				if (!getClient()[getI()]->getBodyToWork()) {
					getClient()[getI()]->_chunck.push_back(getContent(getWww()));
				}
				std::cout << "   \033[0;34mCGI launch\033[0m\n";
				if (_cgi.config_cgi()) throw Response::BuildResponseException();
				setStatusCode(_cgi.getStatu());
            }
        }
	}
	if (getStatusCode() == 200)
	{
		if (getRequest()->getHost().empty()){
			setStatusCode(400);
		}
		else
		{
			std::string host;
			std::string port("80");
			sep[0] = getRequest()->getHost().find(' ');
			sep[1] = getRequest()->getHost().rfind(':');
			if (sep[1] != std::string::npos) port = getRequest()->getHost().substr(sep[1] + 1);
			if (sep[1] == std::string::npos) sep[1] = getRequest()->getHost().length();
			host = getRequest()->getHost().substr(sep[0] + 1, sep[1] - (sep[0] + 1));
			if (!ft_strcmp(host.c_str(), "localhost") || !ft_strcmp(host.c_str(), "127.0.0.1"))
			{
				if (getServer()->getPort() != ft_atoi(port.c_str())) setStatusCode(400);
				else if (ft_strcmp("localhost", getServer()->getHost().c_str()) && ft_strcmp("127.0.0.1", getServer()->getHost().c_str())) setStatusCode(400);
			}
			else if (ft_strcmp(host.c_str(), getServer()->getHost().c_str()) || getServer()->getPort() != ft_atoi(port.c_str())) setStatusCode(400);
		}
		if (getStatusCode() == 400) {
			setListingContent("");
		}
	}
	check_method();
	// std::cout << "   \033[1;34mRESPONSE: \033[0;34m" << std::endl << "\033[0m" << getResponse() << std::endl;
}

void Response::clean()
{
	for (int i = 1; i < FD_SETSIZE; i++)
	{
		if (_allclient[i])
		{
			fd_set tmp;
			tmp = getServer()->getRdFd();
			FD_CLR(i, &tmp);
			tmp = getServer()->getWrFd();
			FD_CLR(i, &tmp);
			close(i);
		}
	}
	delete [] _allclient ;
	delete getRequest();
	if (getServer()->getWrFdAddr()) delete getServer()->getWrFdAddr();
	if (getServer()->getRdFdAddr()) delete getServer()->getRdFdAddr();
	if (getServer()) delete getServer();
	if (getRequest()) {
		delete getRequest();
	}
	if (getServer()->getSocket() > -1) close(getServer()->getSocket());
	delete this;
}

void Response::clear()
{
	_file.clear();
	_method.clear();
	_base.clear();
	_www.clear();
	_listingContent.clear();
	_url.clear();
	_status = 0;
	_i = 0;
	delete _req;
	_req = new Request();
	CGI cgi;
	_cgi = cgi;
}

const char* Response::BuildResponseException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Building response failed\033[0m");
}
