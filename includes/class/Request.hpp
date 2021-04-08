#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <unistd.h>
#include "../../libft-cpp/include/libft.hpp"
#include "../../libft-cpp/include/get_next_line.hpp"

class Request {
    public:
		Request();
		Request(const Request &other);
		Request &operator=(const Request &other);
		~Request();

		void setFirstLine(std::string value);
		void setAcceptCharsets(std::string value);
		void setAcceptLanguage(std::string value);
		void setAuthorization(std::string value);
		void setDate(std::string value);
		void setHost(std::string value);
		void setUserAgent(std::string value);
		void setTime(int value);

		std::string getFirstLine() const;
		std::string getAcceptCharsets() const;
		std::string getAcceptLanguage() const;
		std::string getAuthorization() const;
		std::string getContentType() const;
		std::string getDate() const;
		std::string getHost() const;
		std::string getUserAgent() const;
		int			getTime() const;
		void setTransfetEncoding();

		void config_request(int fd);
		void set_line_config(char *line);

		class GNLMallocException : public std::exception
		{
			public:
				virtual const char* what () const throw();
		};

	private:
		std::string _firstLine;
		std::string _acceptCharsets;
		std::string _acceptLanguage;
		std::string _authorization;
		std::string _date;
		std::string _host;
		std::string _userAgent;
		int			_time;
};

#endif // !REQUEST_HPP