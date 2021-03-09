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
        
		std::string		_listen;
		std::string		_port;
		std::string		_host;
		std::string		_server_name;
		std::string		_limit_client_body;
		std::list<std::string>		*_error_pages;
		std::vector<Routes>	*_routes;
};

#endif // !SERVER_HPP
