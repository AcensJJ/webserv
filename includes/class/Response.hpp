#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include "Request.hpp"
#include "Server.hpp"

class Response {
	public:
		Response();
		Response(const Response &other);
		Response &operator=(const Response &other);
		~Response();

		void	setResponse(std::string value);
		std::string getResponse() const;

		// HEADER ENTITY
		void	setContenLength(std::string content);
		void	setContenType(std::string path);
		// HEADER RESPONSE
		void	setLastModified(std::string path);
		void	setLocation(std::string file, int statuCode);
		void	setRetryAfer(int statuCode);
		void	setServer();
		void	setTransfetEncoding();
		void	setWWWAuthenticate(int statuCode);

		std::string	getContent(std::string path);
		int		statu_code(std::string path, std::vector<Routes> *routes);

		void	getMethod(std::string file, Server *serv);
		// todo
		void	head_method();
		void	put_method();
		void	delete_method();
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
};

#endif // !RESPONSE_HPP