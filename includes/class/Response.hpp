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

		void	set_lastModified(std::string path);
		void	set_content(std::string path);
		int		statu_code(std::string path);
		void	get_method(std::string file, Server *serv);
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