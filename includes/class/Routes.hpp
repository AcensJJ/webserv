#ifndef ROUTES_HPP
#define ROUTES_HPP

#include <string>
#include <list>
#include <iostream>
#include "../../libft-cpp/include/libft.hpp"
#include "../../libft-cpp/include/get_next_line.hpp"
#include <fcntl.h>
#include <unistd.h>

class Routes {

	public:
		Routes();
		Routes(const Routes &other);
		Routes &operator=(const Routes &other);
		~Routes();

		void setDirFile(std::string value);
		void setListen(bool value);
		void setDefault(std::string value);
		void setLocation(std::string value);
		void setGCIPath(std::string value);
		void setGCIExtension(std::string value);
		void setLimitClientBody(std::string value);

		std::string getDirFile() const;
		bool getListen() const;
		std::string getDefault() const;
		std::string getLocation() const;
		std::string getGCIPath() const;
		std::string getGCIExtension() const;
		std::string getLimitClientBody() const;

		std::list<std::string>	*_http_method;
	private:
		std::string		_dir_file;
		bool			_listen;
		std::string		_default;
		std::string		_location;
		std::string		_gci_path;
		std::string		_gci_extension;
		std::string		_limit_client_body;
};

#endif // !ROUTES_HPP