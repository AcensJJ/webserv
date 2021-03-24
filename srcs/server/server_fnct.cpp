#include "global.hpp"

void		exit_err(std::string err, char *freevar, int new_socket, int server_fd)
{
	if (freevar) free(freevar);
	if (new_socket > -1) close(new_socket);
	if (server_fd > -1) close(server_fd);
	std::cout << "\033[1;31m   Error: \033[0;31m " << err << "\033[0m" << std::endl;
	exit(EXIT_FAILURE);
}

int			accept_one_client(int server_fd, sockaddr_in *address)
{
	int new_socket, addrlen = sizeof(address);

	if ((new_socket = accept(server_fd, (struct sockaddr *)address, (socklen_t*)&addrlen)) < 0) 
		std::cout << "\033[1;31m   Error: \033[0;31m accept failed\033[0m" << std::endl; 
	else
	{
		std::cout << "\033[1;32m   Connection: \033[0m accepted" << std::endl;
		fcntl(new_socket, F_SETFL, O_NONBLOCK);
	}
	return (new_socket);
}

static void config_client(fd_set *readfds, fd_set *writefds, int server_fd)
{
	FD_ZERO(readfds);
	FD_ZERO(writefds);
	FD_SET(server_fd , readfds);
	FD_SET(server_fd , writefds);
}

void		waiting_client(Server serv, int server_fd, sockaddr_in *address)
{
	struct timeval	timeout;
	fd_set readfds, writefds;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	config_client(&readfds, &writefds, server_fd);
	waiting_screen();
	while (select(server_fd + 1, &readfds, &writefds, NULL, &timeout) >= 0)
	{
		if (FD_ISSET(server_fd, &readfds)) 
        {
			std::cout << "\x1b[A             "  << std::endl;
			std::cout << "\x1b[A\x1b[A\033[1;35m   new Connection attempt: \033[0m" << std::endl;
			int new_socket;
			if ((new_socket = accept_one_client(server_fd, address)) >= 0)
				one_client(serv, new_socket, server_fd, readfds, writefds);
		}
		else
			std::cout << "\x1b[A             \x1b[A\x1b[A";
		waiting_screen();
		config_client(&readfds, &writefds, server_fd);
	}
	std::cout << "\x1b[A\x1b[A";
	FD_CLR(server_fd, &readfds);
	FD_CLR(server_fd, &writefds);
	exit_err("select failed", NULL, -1, server_fd);
}

void		launch_serv(Server serv)
{
	int server_fd, opt = 1;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) exit_err("socket failed", NULL, -1, -1);
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) exit_err("setsockopt failed", NULL, -1, server_fd);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	if (strcmp(serv.getHost().c_str(), "localhost"))
		address.sin_addr.s_addr = inet_addr(serv.getHost().c_str());
	else
		address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons( serv.getPort() );
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))) exit_err("bind failed", NULL, -1, server_fd);
	if (listen(server_fd, 3)) exit_err("listen failed", NULL, -1, server_fd);
	std::cout << "\033[1;32m   Server launch succesly: \033[0;36mhttp://localhost:" << serv.getPort() << "\033[0m" << std::endl;
	waiting_client(serv, server_fd, &address);
}
