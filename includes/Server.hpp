#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "../libft-cpp/include/libft.hpp"
#include "../libft-cpp/include/get_next_line.hpp"
#include <fcntl.h>
#include <unistd.h>

class Routes {
	public:
		Routes();
		Routes(const Routes &other);
		Routes &operator=(const Routes &other);
		~Routes();

		std::list<std::string>	*_http_method;
		std::string				_dir_file;
		bool					_listen;
		std::string				_default;
		std::string				_location;
		std::string				_gci_path;
		std::string				_gci_extension;
};

class Server {
    public:
		Server();
		Server(const Server &other);
		Server &operator=(const Server &other);
		~Server();

		void setListen(std::string value);
		void setPort(int value);
		void setHost(std::string value);
		void setServerName(std::string value);
		void setLimitClientBody(std::string value);
		void setErrorPages(std::list<std::string> value);
		void setRoutes(std::vector<Routes> value);
		
		std::string getListen() const;
		int getPort() const;
		std::string getHost() const;
		std::string getServerName() const;
		std::string getLimitClientBody() const;
		std::list<std::string> *getErrorPages();
		// std::string getErrorPage() const;
		std::vector<Routes> *getRoutes();
		
		int check_config();

		std::list<std::string>		*_error_pages;
		std::vector<Routes>	*_routes;
	private:
		std::string		_listen;
		int				_port;
		std::string		_host;
		std::string		_server_name;
		std::string		_limit_client_body;
};

#endif // !SERVER_HPP
