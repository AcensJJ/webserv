#include "../../includes/class/CGI.hpp"

CGI::CGI()
{

}

CGI::CGI(const CGI &other)
{
	_env = other.getEnv();
	_auth_type = other.getAuthType();
	_content_length = other.getContentLength();
	_content_type = other.getContentType();
	_gateway_interface = other.getGatewayInterface();
	_path_info = other.getPathInfo();
	_path_translated = other.getPathTranslated();
	_query_string = other.getQueryString();
	_remote_addr = other.getRemoteAddr();
	_remore_ident = other.getRemoteIdent();
	_remote_user = other.getRemoteUser();
	_request_method = other.getRequestMethod();
	_request_uri = other.getRequestUri();
	_script_name = other.getScriptName();
	_server_name = other.getServerName();
	_server_port = other.getServerPort();
	_server_protocol = other.getServerProtocol();
	_server_software = other.getServerSoftware();
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

void			CGI::setAuthType(std::string value)
{
	_auth_type = value;
}

std::string 	CGI::getAuthType() const
{
	return (_auth_type);
}

void			CGI::setContentLength(std::string value)
{
	_content_length = value;
}

std::string 	CGI::getContentLength() const
{
	return (_content_length);
}

void			CGI::setContentType(std::string value)
{
	_content_type = value;
}

std::string 	CGI::getContentType() const
{
	return (_content_type);
}

void			CGI::setGatewayInterface(std::string value)
{
	_gateway_interface = value;
}

std::string 	CGI::getGatewayInterface() const
{
	return (_gateway_interface);
}

void			CGI::setPathInfo(std::string value)
{
	_path_info = value;
}

std::string 	CGI::getPathInfo() const
{
	return (_path_info);
}

void			CGI::setPathTranslated(std::string value)
{
	_path_translated = value;
}

std::string 	CGI::getPathTranslated() const
{
	return (_path_translated);
}

void			CGI::setQueryString(std::string value)
{
	_query_string = value;
}

std::string 	CGI::getQueryString() const
{
	return (_query_string);
}

void			CGI::setRemoteAddr(std::string value)
{
	_remote_addr = value;
}

std::string 	CGI::getRemoteAddr() const
{
	return (_remote_addr);
}

void			CGI::setRemoteIdent(std::string value)
{
	_remore_ident = value;
}

std::string 	CGI::getRemoteIdent() const
{
	return (_remore_ident);
}

void			CGI::setRemoteUser(std::string value)
{
	_remote_user = value;
}

std::string 	CGI::getRemoteUser() const
{
	return (_remote_user);
}

void			CGI::setRequestMethod(std::string value)
{
	_request_method = value;
}

std::string 	CGI::getRequestMethod() const
{
	return (_request_method);
}

void			CGI::setRequestUri(std::string value)
{
	_request_uri = value;
}

std::string 	CGI::getRequestUri() const
{
	return (_request_uri);
}

void			CGI::setScriptName(std::string value)
{
	_script_name = value;
}

std::string 	CGI::getScriptName() const
{
	return (_script_name);
}

void			CGI::setServerName(std::string value)
{
	_server_name = value;
}

std::string 	CGI::getServerName() const
{
	return (_server_name);
}

void			CGI::setServerPort(std::string value)
{
	_server_port = value;
}

std::string 	CGI::getServerPort() const
{
	return (_server_port);
}

void			CGI::setServerProtocol(std::string value)
{
	_server_protocol = value;
}

std::string 	CGI::getServerProtocol() const
{
	return (_server_protocol);
}

void			CGI::setServerSoftware(std::string value)
{
	_server_software = value;
}

std::string 	CGI::getServerSoftware() const
{
	return (_server_software);
}

std::string		CGI::getType()
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

int CGI::set_all_variable(Routes route, Server serv, std::string method, std::string file, std::string content)
{
	char *tmp;
	std::string val;
	if (!(tmp = ft_itoa(content.length()))) return (1);
	val = tmp;
	free(tmp);
	setAuthType("AUTH_TYPE=\"\"");
	setContentLength("CONTENT_LENGTH=\"" + val + "\"");
	if (!ft_strcmp(method.c_str(), "POST") || ft_strcmp(method.c_str(), "PUT")) setContentType("CONTENT_TYPE=\"" + getType() + "\"");
	setGatewayInterface("GATEWAY_INTERFACE=\"CGI/1.1\"");
// 	setPathInfo("PATH_INFO=\"" + var + "\"");
	// setPathTranslated("PATH_TRANSLATED=\"" + val + "\"");
	int pos = file.find("?");
	if (pos == -1) pos = file.length(); 
	val = file.substr(pos, file.length() - pos);
	setQueryString("QUERY_STRING=\"" + val + "\"");
//	setRemoteAddr("REMOTE_ADDR=\"" + var + "\"");
// 	setRemoteIdent("REMOTE_IDENT=\"" + var + "\"");
// 	setRemoteUser("REMOTE_USER=\"" + var + "\"");
	setRequestMethod("REQUEST_METHOD=\"" + method + "\"");
	setRequestUri("REQUEST_URI=\"" + file + "\"");
	setScriptName("SCRIPT_NAME=\"" + route.getGCIPath() + "\"");
	setServerName("SERVER_NAME=\"" + serv.getServerName() + "\"");
	if (!(tmp = ft_itoa(serv.getPort()))) return (1);
	val = tmp;
	free(tmp);
	setServerPort("SERVER_PORT=\"" + val + "\"");
	setServerProtocol("SERVER_PORT=\"HTTP/1.1\"");
	setServerSoftware("SERVER_PORT=\"Nginx\"");
	return (0);
}

int CGI::free_cgi(char **tab, int err)
{
	int i(-1);

	while (tab[++i])
		if (tab[i]) free(tab[i]);
	free(tab);
	if (err) return (1);
	return (0);
}

int CGI::config_cgi(Routes route, Server serv, std::string method, std::string file, std::string content)
{
	char **tmp = getEnv();
	char **env;
	int i(0);

	while (tmp[i])
		i++;
	i += 17;
	if (!ft_strcmp(method.c_str(), "POST") || ft_strcmp(method.c_str(), "PUT")) i++;
	if (!(env = (char **)malloc(i * sizeof(char**))))
		return (1);
	while (--i >= 0)
		env[i] = NULL;
	while (tmp[++i])
		if (!(env[i] = ft_strdup(tmp[i]))) free_cgi(env, 1);
	if (set_all_variable(route, serv, method, file, content)) free_cgi(env, 1);
	if (!(env[i++] = ft_strdup(getAuthType().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getContentLength().c_str()))) return (free_cgi(env, 1));
	if (!ft_strcmp(method.c_str(), "POST") || ft_strcmp(method.c_str(), "PUT"))
		if (!(env[i++] = ft_strdup(getContentType().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getGatewayInterface().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getPathInfo().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getPathTranslated().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getQueryString().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getRemoteAddr().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getRemoteIdent().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getRemoteUser().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getRequestMethod().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getRequestUri().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getScriptName().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getServerName().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getServerPort().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getServerProtocol().c_str()))) return (free_cgi(env, 1));
	if (!(env[i++] = ft_strdup(getServerSoftware().c_str()))) return (free_cgi(env, 1));
	return (free_cgi(env, 0));
}
