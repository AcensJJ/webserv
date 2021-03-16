#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <unistd.h>

class Response {
	public:
		Response();
		Response(const Response &other);
		Response &operator=(const Response &other);
		~Response();

		void setResponse(std::string value);

		std::string getResponse() const;

		void config_response();
	
	class BuildResponseException : public std::exception
	{
		public:
			virtual const char* what () const throw();
	};

	private:
		std::string _response;
};

#endif // !RESPONSE_HPP