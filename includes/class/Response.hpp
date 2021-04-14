#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include "Request.hpp"
#include "Server.hpp"
#define TIMEOUT 500

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
		void		setBase(std::string value);
		std::string getBase() const;
		void		setWww(std::string value);
		std::string getWww() const;
		void		setServer(Server value);
		Server		getServer() const;
		void		setStatusCode(int value);
		int 		getStatusCode() const;

		// HEADER GENERAL
		void	setDate();
		// HEADER ENTITY
		void	setContentLanguage(Request *req);
		void	setContentLength(std::string content);
		void	setContentLocation();
		void	setContentType(Request *req);
		// HEADER RESPONSE
		void	setLastModified(std::string path);
		void	setLocation();
		void	setRetryAfer(Request *req);
		void	setServerNginx();
		void	setWWWAuthenticate();
		
		void	setConnectionClose();

		void	setFirstLine();


		std::string	getContent(std::string path);
		int			statu_code(std::string path, std::vector<Routes> *routes, std::string method);

		void	getMethod(Request *req, int statuCode);

		void	head_method(Request *req, int statuCode);
		void	post_method();
		void	put_method();
		void	delete_method(int statuCode);
		void	connect_method();
		void	options_method();
		void	trace_method();

		void	config_response(Request *req, Server *serv);
	
		class BuildResponseException : public std::exception
		{
			public:
				virtual const char* what () const throw();
		};

	private:
		std::string _response;
		std::string _file;
		std::string _base;
		std::string _www;
		Server		_server;
		int _status;
};

#endif // !RESPONSE_HPP