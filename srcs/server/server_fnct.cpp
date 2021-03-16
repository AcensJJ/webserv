#include "global.hpp"

void	waiting_screen()
{
	std::cout  << std::endl << std::endl << "\033[0;34m   WAITING.\033[0m" << std::endl;
	usleep(500000);
	std::cout  <<  "\x1b[A\033\033[0;34m   WAITING..\033[0m" << std::endl;
	usleep(500000);
	std::cout  <<  "\x1b[A\033\033[0;34m   WAITING...\033[0m" << std::endl;
}

int		config_data_serv(Server serv, int server_fd, int new_socket, int fd_opt)
{
	int request_fd;
	char *dataserv = ft_strjoin("./dataServ/", serv.getServerName().c_str());
	if (!dataserv)
	{
		close(new_socket);
		close(server_fd);
		std::cout << "\033[1;31m   Error: \033[0;31m malloc failed\033[0m" << std::endl;
		exit(EXIT_FAILURE);
	}
	if ((request_fd = open(dataserv, fd_opt, 0644)) < 0)
	{
		free(dataserv);
		close(new_socket);
		close(server_fd);
		std::cout << "\033[1;31m   Error: \033[0;31m open failed\033[0m" << std::endl;
		exit(EXIT_FAILURE);
	}
	free(dataserv);
	return (request_fd);
}

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
