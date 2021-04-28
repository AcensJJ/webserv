#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include "../../libft-cpp/include/libft.hpp"
#include "../../libft-cpp/include/get_next_line.hpp"
#include <fcntl.h>
#include <unistd.h>

#include "class/Routes.hpp"
#include "class/Server.hpp"
#include "class/Request.hpp"

class CGI {
    public:
		CGI();
		CGI(const CGI &other);
		~CGI();
		CGI &operator=(const CGI &other);

		void			setEnv(char **value);
		char 			**getEnv() const;
		void			setAuthType(std::string value);
		std::string 	getAuthType() const;
		void			setContentLength(std::string value);
		std::string 	getContentLength() const;
		void			setContentType(std::string value);
		std::string 	getContentType() const;
		void			setGatewayInterface(std::string value);
		std::string 	getGatewayInterface() const;
		void			setPathInfo(std::string value);
		std::string 	getPathInfo() const;
		void			setPathTranslated(std::string value);
		std::string 	getPathTranslated() const;
		void			setQueryString(std::string value);
		std::string 	getQueryString() const;
		void			setRemoteAddr(std::string value);
		std::string 	getRemoteAddr() const;
		void			setRemoteIdent(std::string value);
		std::string 	getRemoteIdent() const;
		void			setRemoteUser(std::string value);
		std::string 	getRemoteUser() const;
		void			setRequestMethod(std::string value);
		std::string 	getRequestMethod() const;
		void			setRequestUri(std::string value);
		std::string 	getRequestUri() const;
		void			setScriptName(std::string value);
		std::string 	getScriptName() const;
		void			setServerName(std::string value);
		std::string 	getServerName() const;
		void			setServerPort(std::string value);
		std::string 	getServerPort() const;
		void			setServerProtocol(std::string value);
		std::string 	getServerProtocol() const;
		void			setServerSoftware(std::string value);
		std::string 	getServerSoftware() const;

		std::string		getType();

		int			set_all_variable(Routes route, Server serv, std::string method, std::string file, std::string content);
		int			free_cgi(char **tab, int err);
		int			config_cgi(Routes route, Server serv, std::string method, std::string file, std::string content);

	private:
		char **_env;
		std::string _auth_type;
		std::string _content_length;
		std::string _content_type;
		std::string _gateway_interface;
		std::string _path_info;
		std::string _path_translated;
		std::string _query_string;
		std::string _remote_addr;
		std::string _remore_ident;
		std::string _remote_user;
		std::string _request_method;
		std::string _request_uri;
		std::string _script_name;
		std::string _server_name;
		std::string _server_port;
		std::string _server_protocol;
		std::string _server_software;
};

#endif // !CGI_HPP