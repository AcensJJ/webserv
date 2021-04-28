#include "../../includes/class/CGI.hpp"

CGI::CGI()
{

}

CGI::CGI(const CGI &other)
{
	_env = other.getEnv();
}

CGI::~CGI()
{

}

CGI &CGI::operator=(const CGI &other)
{
    if (this == &other) return(*this);
    this->~CGI();
    return *new(this) CGI(other);
}

void CGI::setEnv(char **value)
{
	this->_env = value;
}

char** CGI::getEnv() const
{
	return(this->_env);
}

void CGI::setRoutes(Routes value)
{
	_route = value;
}

Routes CGI::getRoutes() const
{
	return(_route);
}

void CGI::setServer(Server value)
{
	_serv = value;
}

Server CGI::getServer() const
{
	return(_serv);
}

void CGI::setMethod(std::string value)
{
	_method = value;
}

std::string CGI::getMethod() const
{
	return(_method);
}

void CGI::setFile(std::string value)
{
	_file = value;
}

std::string CGI::getFile() const
{
	return(_file);
}

void CGI::setContent(std::string value)
{
	_content = value;
}

std::string CGI::getContent() const
{
	return(_content);
}

void CGI::setClient(Client* value)
{
	_client = value;
}

Client* CGI::getClient() const
{
	return(_client);
}

std::string CGI::getType()
{
	std::string type;
	if (!ft_strcmp(type.c_str() , ".aac"))	 return ("audio/aac");
	if (!ft_strcmp(type.c_str() , ".abw"))	 return ("application/x-abiword");
	if (!ft_strcmp(type.c_str() , ".arc"))	 return ("application/octet-stream");
	if (!ft_strcmp(type.c_str() , ".avi"))	 return ("video/x-msvideo");
	if (!ft_strcmp(type.c_str() , ".azw"))	 return ("application/vnd.amazon.ebook");
	if (!ft_strcmp(type.c_str() , ".bin"))	 return ("application/octet-stream");
	if (!ft_strcmp(type.c_str() , ".bmp"))	 return ("image/bmp");
	if (!ft_strcmp(type.c_str() , ".bz"))	 return ("application/x-bzip");
	if (!ft_strcmp(type.c_str() , ".bz2"))	 return ("application/x-bzip2");
	if (!ft_strcmp(type.c_str() , ".csh"))	 return ("application/x-csh");
	if (!ft_strcmp(type.c_str() , ".css"))	 return ("text/css");
	if (!ft_strcmp(type.c_str() , ".csv"))	 return ("text/csv");
	if (!ft_strcmp(type.c_str() , ".doc"))	 return ("application/msword");
	if (!ft_strcmp(type.c_str() , ".docx"))	 return ("pplication/vnd.openxmlformats-officedocument.wordprocessingml.document");
	if (!ft_strcmp(type.c_str() , ".eot"))	 return ("application/vnd.ms-fontobject");
	if (!ft_strcmp(type.c_str() , ".epub"))	 return ("application/epub+zip");
	if (!ft_strcmp(type.c_str() , ".gif"))	 return ("image/gif");
	if (!ft_strcmp(type.c_str() , ".htm"))	 return ("text/html");
	if (!ft_strcmp(type.c_str() , ".html"))	 return ("text/html");
	if (!ft_strcmp(type.c_str() , ".ico"))	 return ("image/x-icon");
	if (!ft_strcmp(type.c_str() , ".ics"))	 return ("text/calendar");
	if (!ft_strcmp(type.c_str() , ".jar"))	 return ("application/java-archive");
	if (!ft_strcmp(type.c_str() , ".jpg"))	 return ("image/jpeg");
	if (!ft_strcmp(type.c_str() , ".jpeg"))	 return ("image/jpeg");
	if (!ft_strcmp(type.c_str() , ".js"))	 return ("application/javascript");
	if (!ft_strcmp(type.c_str() , ".json"))	 return ("application/json");
	if (!ft_strcmp(type.c_str() , ".mid"))	 return ("audio/midi");
	if (!ft_strcmp(type.c_str() , ".midi"))	 return ("audio/midi");
	if (!ft_strcmp(type.c_str() , ".mpeg"))	 return ("video/mpeg");
	if (!ft_strcmp(type.c_str() , ".mpkg"))	 return ("application/vnd.apple.installer+xml");
	if (!ft_strcmp(type.c_str() , ".odp"))	 return ("application/vnd.oasis.opendocument.presentation");
	if (!ft_strcmp(type.c_str() , ".ods"))	 return ("application/vnd.oasis.opendocument.spreadsheet");
	if (!ft_strcmp(type.c_str() , ".odt"))	 return ("application/vnd.oasis.opendocument.text");
	if (!ft_strcmp(type.c_str() , ".oga"))	 return ("audio/ogg");
	if (!ft_strcmp(type.c_str() , ".ogv"))	 return ("video/ogg");
	if (!ft_strcmp(type.c_str() , ".ogx"))	 return ("application/ogg");
	if (!ft_strcmp(type.c_str() , ".otf"))	 return ("font/otf");
	if (!ft_strcmp(type.c_str() , ".png"))	 return ("image/png");
	if (!ft_strcmp(type.c_str() , ".pdf"))	 return ("application/pdf");
	if (!ft_strcmp(type.c_str() , ".ppt"))	 return ("application/vnd.ms-powerpoint");
	if (!ft_strcmp(type.c_str() , ".pptx"))	 return ("application/vnd.openxmlformats-officedocument.presentationml.presentation");
	if (!ft_strcmp(type.c_str() , ".rar"))	 return ("application/x-rar-compressed");
	if (!ft_strcmp(type.c_str() , ".rtf"))	 return ("application/rtf");
	if (!ft_strcmp(type.c_str() , ".sh"))	 return ("application/x-sh");
	if (!ft_strcmp(type.c_str() , ".svg"))	 return ("image/svg+xml");
	if (!ft_strcmp(type.c_str() , ".swf"))	 return ("application/x-shockwave-flash");
	if (!ft_strcmp(type.c_str() , ".tar"))	 return ("application/x-tar");
	if (!ft_strcmp(type.c_str() , ".tif"))	 return ("image/tiff");
	if (!ft_strcmp(type.c_str() , ".tiff"))	 return ("image/tiff");
	if (!ft_strcmp(type.c_str() , ".ts"))	 return ("application/typescript");
	if (!ft_strcmp(type.c_str() , ".ttf"))	 return ("font/ttf");
	if (!ft_strcmp(type.c_str() , ".vsd"))	 return ("application/vnd.visio");
	if (!ft_strcmp(type.c_str() , ".wav"))	 return ("audio/x-wav");
	if (!ft_strcmp(type.c_str() , ".weba"))	 return ("audio/webm");
	if (!ft_strcmp(type.c_str() , ".webm"))	 return ("video/webm");
	if (!ft_strcmp(type.c_str() , ".webp"))	 return ("image/webp");
	if (!ft_strcmp(type.c_str() , ".woff"))	 return ("font/woff");
	if (!ft_strcmp(type.c_str() , ".woff2")) return ("font/woff2");
	if (!ft_strcmp(type.c_str() , ".xhtml")) return ("application/xhtml+xml");
	if (!ft_strcmp(type.c_str() , ".xls"))	 return ("application/vnd.ms-excel");
	if (!ft_strcmp(type.c_str() , ".xlsx"))	 return ("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
	if (!ft_strcmp(type.c_str() , ".xml"))	 return ("application/xml");
	if (!ft_strcmp(type.c_str() , ".xul"))	 return ("application/vnd.mozilla.xul+xml");
	if (!ft_strcmp(type.c_str() , ".zip"))	 return ("application/zip");
	if (!ft_strcmp(type.c_str() , ".3gp"))	 return ("video/3gpp");
	if (!ft_strcmp(type.c_str() , ".3g2"))	 return ("video/3gpp2");
	if (!ft_strcmp(type.c_str() , ".7z"))	 return ("application/x-7z-compressed");
	return ("");

}

int CGI::set_all_variable(std::list<std::string> metavar)
{
	char *tmp;
	std::string val;
	if (!(tmp = ft_itoa(getContent().length()))) return (1);
	val = tmp;
	free(tmp);
	// metavar.push_back("AUTH_TYPE=\"" + var + "\"");
	metavar.push_back("CONTENT_LENGTH=\"" + val + "\"");
	if (!ft_strcmp(getMethod().c_str(), "POST") || ft_strcmp(getMethod().c_str(), "PUT")) metavar.push_back("CONTENT_TYPE=\"" + getType() + "\"");
	metavar.push_back("GATEWAY_INTERFACE=\"CGI/1.1\"");
	size_t pos = getRoutes().getGCIPath().rfind("/");
	if (pos != std::string::npos) { 
		val = getRoutes().getGCIPath().substr(pos, getRoutes().getGCIPath().length() - pos);
		metavar.push_back("PATH_INFO=\"" + val + "\"");
		metavar.push_back("PATH_TRANSLATED=\"." +  getRoutes().getGCIPath() + "\"");
	}
	pos = getFile().find("?");
	if (pos == std::string::npos) pos = getFile().length(); 
	val = getFile().substr(pos, getFile().length() - pos);
	metavar.push_back("QUERY_STRING=\"" + val + "\"");
	// metavar.push_back("REMOTE_ADDR=\"" + getClient()->getAddres()->sin_addr->sin_addr + "\"");
	// metavar.push_back("REMOTE_IDENT=\"" + getClient()->getAddres()-> + "\"");
	// metavar.push_back("REMOTE_USER=\"" + getClient()->getAddres()-> + "\"");
	metavar.push_back("REQUEST_METHOD=\"" + getMethod() + "\"");
	metavar.push_back("REQUEST_URI=\"" + getFile() + "\"");
	metavar.push_back("SCRIPT_NAME=\"" + getRoutes().getGCIPath() + "\"");
	metavar.push_back("SERVER_NAME=\"" + getServer().getServerName() + "\"");
	if (!(tmp = ft_itoa(getServer().getPort()))) return (1);
	val = tmp;
	free(tmp);
	metavar.push_back("SERVER_PORT=\"" + val + "\"");
	metavar.push_back("SERVER_PORT=\"HTTP/1.1\"");
	metavar.push_back("SERVER_PORT=\"Nginx\"");
	if (!getClient()->getRequest()->getAcceptCharsets().empty())   metavar.push_back("HTTP_ACCEPT_CHARSETS="   + getClient()->getRequest()->getAcceptCharsets() + "\"");
	if (!getClient()->getRequest()->getAcceptLanguage().empty())   metavar.push_back("HTTP_ACCEPT_LANGUAGE="   + getClient()->getRequest()->getAcceptLanguage() + "\"");
	if (!getClient()->getRequest()->getAuthorization().empty())    metavar.push_back("HTTP_AUTHORIZATION="     + getClient()->getRequest()->getAuthorization()  + "\"");
	if (!getClient()->getRequest()->getDate().empty())             metavar.push_back("HTTP_DATE="              + getClient()->getRequest()->getDate()           + "\"");
	if (!getClient()->getRequest()->getHost().empty())             metavar.push_back("HTTP_HOST="              + getClient()->getRequest()->getHost() + "\"");
	if (!getClient()->getRequest()->getUserAgent().empty())        metavar.push_back("HTTP_USER_AGENT="        + getClient()->getRequest()->getUserAgent() + "\"");
	if (!getClient()->getRequest()->getTransferEncoding().empty()) metavar.push_back("HTTP_TRANSFER_ENCODING=" + getClient()->getRequest()->getTransferEncoding() + "\"");
	if (!getClient()->getRequest()->getReferer().empty())          metavar.push_back("HTTP_REFERER="           + getClient()->getRequest()->getReferer() + "\"");
	return (0);
}

int CGI::free_cgi(char **tab, int err)
{
	int i(-1);

	while (tab[++i])
		if (tab[i]) free(tab[i]);
	free(tab);
	return (err);
}

int CGI::config_cgi(Routes route, Server serv, std::string method, std::string file, std::string content, Client *client)
{
	char **tmp = getEnv();
	char **env;
	int i(0);
	setRoutes(route);
	setServer(serv);
	setMethod(method);
	setFile(file);
	setContent(content);
	setClient(client);
	std::list<std::string> metavar;

	while (tmp[i])
		i++;
	i += metavar.size();
	if (!(env = (char **)malloc(++i * sizeof(char**))))
		return (1);
	while (--i >= 0)
		env[i] = NULL;
	while (tmp[++i])
		if (!(env[i] = ft_strdup(tmp[i]))) free_cgi(env, 1);
	for (std::list<std::string>::iterator itr = metavar.begin(); itr != metavar.end(); itr++)
		if (!(env[++i] = ft_strdup(itr->c_str()))) free_cgi(env, 1);
	return (free_cgi(env, 0));
}
