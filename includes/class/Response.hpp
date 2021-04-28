#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include "global.hpp"

class Routes;

class Response {
	public:
		Response();
		Response(const Response &other);
		Response &operator=(const Response &other);
		~Response();

		void		setResponse(std::string value);
		std::string getResponse() const;
		void		setFile(std::string value);
		std::string getFile() const;
		void		setMethod(std::string value);
		std::string getMethod() const;
		void		setBase(std::string value);
		std::string getBase() const;
		void		setWww(std::string value);
		std::string getWww() const;
		void		setServer(Server value);
		Server		getServer() const;
		void		setStatusCode(int value);
		int 		getStatusCode() const;
		void		setRoutes(Routes value);
		Routes 		getRoutes() const;
		void		setListingContent(std::string value);
		std::string getListingContent() const;
		void		setEnv(char **value);
		char 		**getEnv() const;

		void 		configDefault();
		void 		configMethod();

		// HEADER GENERAL
		void	setDate();
		// HEADER ENTITY
		void	setAllow();
		void	setContentLanguage(Request *req);
		void	setContentLength(std::string content);
		void	setContentLocation();
		void	setContentType(Request *req);
		// HEADER RESPONSE
		void	setLastModified(std::string path);
		void	setLocation();
		void	setRetryAfer(Request *req);
		void	setServerNginx();
		void	setWWWAuthenticate(Request *req);
		
		void	setConnectionClose();

		void	setFirstLine();

		std::string	getContent(std::string path);
		int			print_directory(const char *path);
		int			check_exist(std::string path);
		int			statu_code(std::string path);

		void	setAllHeader(Request *req);

		void	get_method(Request *req);
		void	head_method(Request *req);
		void	post_method(Request *req);
		void	put_method(Request *req);
		void	delete_method(Request *req);
		void	connect_method(Request *req);
		void	options_method(Request *req);
		void	trace_method(Request *req);

		void	check_method(Request *req);
		void	config_response(Request *req, Server *serv, char **env);
	
		class BuildResponseException : public std::exception
		{
			public:
				virtual const char* what () const throw();
		};

		std::map<std::string, std::string>	_http_method;
		std::map<std::string, std::string>	_default;
	private:
		std::string _response;
		std::string _file;
		std::string _method;
		std::string _base;
		std::string _www;
		Server		_server;
		int			_status;
		Routes		_routes;
		std::string _listingContent;
		char		**_env;

};

#endif // !RESPONSE_HPP