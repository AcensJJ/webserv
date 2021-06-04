#include "../../includes/class/CGI.hpp"

CGI::CGI()
{
	_do = false;
}

CGI::CGI(const CGI &other)
{
	_env = other.getEnv();
	_route = other.getRoutes();
	_req = other.getRequest();
	_serv = other.getServer();
	_method = other.getMethod();
	_file = other.getFile();
	_content = other.getContent();
	_body = other.getBody();
	_statu = other.getStatu();
	_client = other.getClient();
	_do = other.getDo();
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

void CGI::setRequest(Request *value)
{
	_req = value;
}

Request* CGI::getRequest() const
{
	return (_req);
}

void CGI::setServer(Server* value)
{
	_serv = value;
}

Server* CGI::getServer() const
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

void CGI::setBody(std::string value)
{
	_body = value;
}

std::string CGI::getBody() const
{
	return(_body);
}

void CGI::setStatu(int value)
{
	_statu = value;
}

int CGI::getStatu() const
{
	return(_statu);
}

void CGI::setClient(Client* value)
{
	_client = value;
}

Client* CGI::getClient() const
{
	return(_client);
}

void CGI::setDo(bool value)
{
	_do = value;
}

bool CGI::getDo() const
{
	return(_do);
}


std::string CGI::getType()
{
	std::string type = getFile().substr(getFile().find_last_of("."),getFile().length());
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

int CGI::set_all_variable(std::list<std::string> *metavar)
{
	char *tmp;
	std::string val;
	int nb = 0;
	for (std::list<std::string>::iterator itr = getClient()->_chunck.begin(); itr != getClient()->_chunck.end(); itr++)
		nb += itr->length();
	if (!(tmp = ft_itoa(nb))) return (1);
	val = tmp;
	free(tmp);
	if (ft_strcmp(getClient()->getLogin().c_str(), "NotAuth") && ft_strcmp(getClient()->getLogin().c_str(), "Error")) metavar->push_back("AUTH_TYPE=Basic");
	metavar->push_back("CONTENT_LENGTH=" + val + "");
	if (!ft_strcmp(getMethod().c_str(), "POST") || !ft_strcmp(getMethod().c_str(), "PUT")) metavar->push_back("CONTENT_TYPE=" + getType() + "");
	metavar->push_back("GATEWAY_INTERFACE=CGI/1.1");
	size_t pos = getRoutes().getCGIPath().rfind("/");
	if (pos != std::string::npos) { 
		val = getRoutes().getCGIPath().substr(pos, getRoutes().getCGIPath().length() - pos);
		metavar->push_back("PATH_INFO=" + getFile());
		metavar->push_back("PATH_TRANSLATED=." +  getRoutes().getCGIPath() + "");
	}
	pos = getFile().find("?");
	if (pos == std::string::npos) pos = getFile().length(); 
	val = getFile().substr(pos, getFile().length() - pos);
	metavar->push_back("QUERY_STRING=");
	metavar->push_back("REMOTE_ADDR=" + getServer()->getHost() + "");
	metavar->push_back("REMOTE_IDENT=""");
	metavar->push_back("REMOTE_USER=" + getClient()->getLogin().substr(0, getClient()->getLogin().find(":")) + "");
	metavar->push_back("REQUEST_METHOD=" + getMethod() + "");
	metavar->push_back("SCRIPT_NAME=" + getRoutes().getCGIPath() + "");
	metavar->push_back("SERVER_NAME=" + getServer()->getServerName() + "");
	if (!(tmp = ft_itoa(getServer()->getPort()))) return (1);
	val = tmp;
	free(tmp);
	metavar->push_back("REQUEST_URI="+ getFile());
	metavar->push_back("SERVER_PORT=" + val + "");
	metavar->push_back("SERVER_PROTOCOL=HTTP/1.1");
	metavar->push_back("SERVER_SOFTWARE=Nginx");
	if (!getRequest()->getAcceptCharsets().empty())   metavar->push_back("HTTP_ACCEPT_CHARSETS="   + (std::string)&getRequest()->getAcceptCharsets().at(17) + "");
	if (!getRequest()->getAcceptLanguage().empty())   metavar->push_back("HTTP_ACCEPT_LANGUAGE="   + (std::string)&getRequest()->getAcceptLanguage().at(17) + "");
	if (!getRequest()->getAuthorization().empty())    metavar->push_back("HTTP_AUTHORIZATION="     + (std::string)&getRequest()->getAuthorization().at(15)  + "");
	if (!getRequest()->getDate().empty())             metavar->push_back("HTTP_DATE="              + (std::string)&getRequest()->getDate().at(6)           + "");
	if (!getRequest()->getHost().empty())             metavar->push_back("HTTP_HOST="              + (std::string)&getRequest()->getHost().at(6) + "");
	if (!getRequest()->getUserAgent().empty())        metavar->push_back("HTTP_USER_AGENT="        + (std::string)&getRequest()->getUserAgent().at(12) + "");
	if (!getRequest()->getTransferEncoding().empty()) metavar->push_back("HTTP_TRANSFER_ENCODING=" + (std::string)&getRequest()->getTransferEncoding().at(19) + "");
	if (!getRequest()->getReferer().empty())          metavar->push_back("HTTP_REFERER="           + (std::string)&getRequest()->getReferer().at(9) + "");
	return (0);
}

int CGI::free_cgi(char **tab, int err)
{
	int i(-1);

	if (tab)
	{
		while (tab[++i])
			if (tab[i]) free(tab[i]);
		free(tab);
	}
	return (err);
}

int CGI::config_cgi()
{
	_do = true;
	char **tmp = getEnv();
	char **env;
	int i(0);
	std::list<std::string> metavar;

	if (set_all_variable(&metavar)) return (1);
	while (tmp[i])
		i++;
	i += metavar.size();
	if (!(env = (char **)malloc(++i * sizeof(char**))))
		return (1);
	while (--i >= 0)
		env[i] = NULL;
	while (tmp[++i])
		if (!(env[i] = ft_strdup(tmp[i]))) return (free_cgi(env, 1));
	for (std::list<std::string>::iterator itr = metavar.begin(); itr != metavar.end(); itr++)
	{
		if (!(env[i++] = ft_strdup(itr->c_str()))) return (free_cgi(env, 1));
	}
	setEnv(env);
	execv();
	return (free_cgi(getEnv(), 0));
}

int CGI::execv()
{
	int pfd[2];
	int pfd2[2];
	int fdfile;
	pid_t pid;
	if (pipe(pfd) == -1 || pipe(pfd2) == -1)
		throw CGI::CGIException();
	if ((fdfile = open((DATA_SERV + getServer()->getServerName()).c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
		throw CGI::CGIException();
	pid = fork();
	if (pid == -1)
		throw CGI::CGIException();
	else if (pid == 0)
	{
		dup2(pfd[0], STDIN_FILENO);
        close(pfd[0]);
        close(pfd[1]);
        dup2(fdfile, STDOUT_FILENO);
        dup2(pfd2[1], fdfile);
        close(pfd2[0]);
        close(pfd[1]);
		if (execve(getRoutes().getCGIPath().c_str(), NULL, getEnv()) < 0)
			throw CGI::CGIException();
		close(pfd[1]);
		exit(0);
	}
    else
    {
        close(pfd[0]);
		for (std::list<std::string>::iterator itr = getClient()->_chunck.begin(); itr != getClient()->_chunck.end(); itr++)
			write(pfd[1], itr->c_str(), itr->length());
        close(pfd[1]);
        close(pfd2[1]);
        close(pfd2[0]);
        if (fdfile) close(fdfile);
		waitpid(pid, NULL, 0);
		if (fdfile) close(fdfile);
		close(pfd[0]);
    }
	std::ifstream fs(DATA_SERV + getServer()->getServerName());
	if (fs.is_open())
	{
		std::stringstream ss;
		ss << fs.rdbuf();
		fs.close();
		std::string check = ss.str();
		size_t j;
		if ((j = check.find("Status:")) != std::string::npos) setStatu(ft_atoi(&check[j + 7]));
		if ((j = check.find("\r\n\r\n")) != std::string::npos)
		{
			std::string tmp = &check[j + 4];
			if (tmp.length() >= 4) tmp.erase(tmp.length() - 4, 4);
			setBody(tmp);
		}
	}
	return (0);
}

const char* CGI::CGIException::what() const throw ()
{
	return ("\033[1;31m   Error: \033[0;31m Building CGI failed\033[0m");
}
