#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#define TIMEOUT 500
#define SERV_WWW "./server/www/"

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <vector>
#include <list>
#include <map>
#include <dirent.h>
#include <algorithm>
#include <cstdlib>

#include "../libft-cpp/include/libft.hpp"
#include "../libft-cpp/include/get_next_line.hpp"

#include "class/Client.hpp"
#include "class/Server.hpp"
#include "class/Request.hpp"
#include "class/CGI.hpp"

class Request;

class Server;

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
		void		setUrl(std::string value);
		std::string getUrl() const;
		void		setServer(Server* value);
		Server*		getServer() const;
		void		setStatusCode(int value);
		int 		getStatusCode() const;
		void		setI(int value);
		int 		getI() const;
		void		setRoutes(Routes value);
		Routes 		getRoutes() const;
		void		setListingContent(std::string value);
		std::string getListingContent() const;
		void		setRequest(Request* value);
		Request*	getRequest() const;
		void		setClient(Client** value);
		Client**	getClient() const;
		void		setBodyToWork(bool value);
		bool		getBodyToWork() const;

		void 		configDefault();
		void 		configMethod();

		// HEADER GENERAL
		void	setDate();
		// HEADER ENTITY
		void	setAllow();
		void	setContentLanguage();
		void	setContentLength(std::string content);
		void	setContentLocation();
		void	setContentType();
		// HEADER RESPONSE
		void	setLastModified(std::string path);
		void	setLocation();
		void	setRetryAfer();
		void	setServerNginx();
		void	setWWWAuthenticate();
		
		void	setConnectionClose();

		void	setFirstLine();

		std::string	getContent(std::string path);
		int			print_directory(const char *path);
		int			check_exist(std::string path);
		int			statu_code(std::string path);

		void	setAllHeader();

		void	get_method();
		void	head_method();
		void	post_method();
		void	put_method();
		void	delete_method();

		void	check_method();
		void	config_response(char **env, int i);

		void clear();
		void clean();
	
		class BuildResponseException : public std::exception
		{
			public:
				virtual const char* what () const throw();
		};

		std::map<std::string, std::string>	_http_method;
		std::map<std::string, std::string>	_default;
	private:
		std::string _response, _file, _method, _base, _www, _listingContent, _url;
		Server		*_server;
		Routes		_routes;
		int			_status, _i;
		Client		**_allclient;
		Request		*_req;
		CGI 		_cgi;
		bool		_work;


};

#endif // !RESPONSE_HPP