#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include "../../libft-cpp/include/libft.hpp"
#include "../../libft-cpp/include/get_next_line.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include <list>
#include "class/Routes.hpp"
#include "class/Server.hpp"
#include "class/Client.hpp"
#include "class/Request.hpp"

#define DATA_SERV "./server/dataServ/"

 class CGI {
     public:
 		CGI();
 		CGI(const CGI &other);
 		~CGI();
 		CGI &operator=(const CGI &other);

 		void			setEnv(char **value);
 		char 			**getEnv() const;
 		void			setRoutes(Routes value);
 		Routes 			getRoutes() const;
 		void			setRequest(Request* value);
 		Request 		*getRequest() const;
 		void			setServer(Server* value);
 		Server 			*getServer() const;
 		void			setMethod(std::string value);
 		std::string 	getMethod() const;
 		void			setFile(std::string value);
 		std::string 	getFile() const;
 		void			setContent(std::string value);
 		std::string 	getContent() const;
 		void			setBody(std::string value);
 		std::string 	getBody() const;
 		void			setStatu(int value);
 		int 			getStatu() const;
 		void			setClient(Client* value);
 		Client	 		*getClient() const;
 		void			setDo(bool value);
 		bool	 		getDo() const;

 		std::string		getType();

 		int			set_all_variable(std::list<std::string> *metavar);
 		int			free_cgi(char **tab, int err);
 		int			config_cgi();
		int			execv();

		class CGIException : public std::exception
		{
			public:
				virtual const char* what () const throw();
		};

 	private:
 		char **_env;
 		Routes _route;
 		Request *_req;
 		Server *_serv;
 		std::string _method, _file, _content, _body;
		int _statu;
 		Client *_client;
		bool _do;
 };

 #endif // !CGI_HPP