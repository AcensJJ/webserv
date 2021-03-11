#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <unistd.h>

class REQUEST {
    public:
		REQUEST();
		REQUEST(const REQUEST &other);
		REQUEST &operator=(const REQUEST &other);
		~REQUEST();

	private:
		std::string acceptCharsets;
		std::string acceptLanguage;
		std::string allow;
		std::string authorization;
		std::string contentLanguage;
		std::string contentLength;
		std::string contentLocation;
		std::string contentType;
		std::string date;
		std::string host;
		std::string lastModified;
		std::string location;
		std::string referer;
		std::string retryAfter;
		std::string server;
		std::string transferEncoding;
		std::string userAgent;
		std::string wwwAuthenticate;
};


#endif // !REQUEST_HPP