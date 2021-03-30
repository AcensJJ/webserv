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
		void	setLastModified(std::string path);
		void	setContenLength(std::string content);
		void	setContenType(std::string path);

		std::string getResponse() const;
		std::string	getContent(std::string path);
		void	getMethod(std::string file, Server *serv);

		int		statu_code(std::string path);

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