#include "global.hpp"

int		accept_one_client(int server_fd, sockaddr_in *address)
{
	int new_socket;
	int addrlen = sizeof(address);

	if ((new_socket = accept(server_fd, (struct sockaddr *)address, (socklen_t*)&addrlen)) < 0) 
		std::cout << "\033[1;31m   Error: \033[0;31m accept failed\033[0m" << std::endl; 
	else
	{
		std::cout << "\033[1;32m   Connection: \033[0m accepted" << std::endl;
		if (fcntl(new_socket, F_SETFL, O_NONBLOCK) < 0) 
			std::cout << "\033[1;31m   Error: \033[0;31m fcntl failed\033[0m" << std::endl;
	}
	return (new_socket);
}

void	waiting_client(Server serv, char **env, int server_fd, sockaddr_in *address)
{
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	waiting_screen();
	while (select(server_fd + 1, NULL, NULL, NULL, &timeout) >= 0)
	{
		std::cout << "\x1b[A\x1b[A";
		std::cout << "\033[1;35m   New connection attempt: \033[0m" << std::endl;
		int new_socket;
		if ((new_socket = accept_one_client(server_fd, address)) >= 0)
			one_client(serv, env, new_socket, server_fd);
		waiting_screen();
	}
	std::cout << "\x1b[A\033[1;31m   Error: \033[0;31m select failed\033[0m" << std::endl;
	close(server_fd);
	exit(EXIT_FAILURE);
}

void	launch_serv(Server serv, char **env)
{
	int server_fd;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cout << "\033[1;31m   Error: \033[0;31m socket failed\033[0m" << std::endl;
		exit(EXIT_FAILURE);
	}
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		close(server_fd);
		std::cout << "\033[1;31m   Error: \033[0;31m setsockopt\033[0m" << std::endl;
		exit(EXIT_FAILURE);
	}
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	if (strcmp(serv.getHost().c_str(), "localhost"))
		address.sin_addr.s_addr = inet_addr(serv.getHost().c_str());
	else
		address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons( serv.getPort() );
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)))
	{
		close(server_fd);
		std::cout << "\033[1;31m   Error: \033[0;31m bind failed\033[0m" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3))
	{
		close(server_fd);
		std::cout << "\033[1;31m   Error: \033[0;31m listen failed\033[0m" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "\033[1;32m   Server launch succesly: \033[0;36mhttp://localhost:" << serv.getPort() << "\033[0m" << std::endl;
	waiting_client(serv, env, server_fd, &address);
}
