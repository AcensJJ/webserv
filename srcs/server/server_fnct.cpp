#include "global.hpp"

void	exit_err(std::string err, char *freevar, int new_socket, int server_fd)
{
	if (freevar) free(freevar);
	if (new_socket > -1) close(new_socket);
	if (server_fd > -1) close(server_fd);
	std::cout << "\033[1;31m   Error: \033[0;31m " << err << "\033[0m" << std::endl;
	exit(EXIT_FAILURE);
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

static int config_client(fd_set *readfds, int *client_socket, int max_clients, int max_sd, int server_fd)
{
	int sd, i;
	FD_ZERO(readfds);
	// FD_CLR(server_fd , readfds);
	FD_SET(server_fd , readfds);
	//add child sockets to set
	for ( i = 0 ; i < max_clients ; i++) 
	{
		//socket descriptor
		sd = client_socket[i];
		//if valid socket descriptor then add to read list
		if(sd > 0)
			FD_SET( sd , readfds);
		//highest file descriptor number, need it for the select function
		if(sd > max_sd)
			max_sd = sd;
	}
	return (max_sd);
}

void	waiting_client(Server serv, char **env, int server_fd, sockaddr_in *address)
{
	struct timeval	timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	fd_set readfds;
	int max_sd = server_fd, client_socket[30], max_clients = 30;
 	//initialise all client_socket[] to 0 so not checked
	for (int i = 0; i < max_clients; i++) 
		client_socket[i] = 0;
	max_sd = config_client(&readfds, client_socket, max_clients, max_sd, server_fd);
	waiting_screen();
	while (select(max_sd + 1, &readfds, NULL, NULL, &timeout) >= 0)
	{
		if (FD_ISSET(server_fd, &readfds)) 
        {
			std::cout << "\x1b[A             "  << std::endl;
			std::cout << "\x1b[A\x1b[A\033[1;35m   New connection attempt: \033[0m" << std::endl;
			int new_socket;
			if ((new_socket = accept_one_client(server_fd, address)) >= 0)
				one_client(serv, env, new_socket, server_fd, readfds);
		}
		else
			std::cout << "\x1b[A             \x1b[A\x1b[A";
		waiting_screen();
		max_sd = config_client(&readfds, client_socket, max_clients, max_sd, server_fd);
	}
	std::cout << "\x1b[A\x1b[A";
	FD_CLR(server_fd, &readfds);
	exit_err("select failed", NULL, -1, server_fd);
}

void	launch_serv(Server serv, char **env)
{
	int server_fd;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) exit_err("socket failed", NULL, -1, -1);
	int opt = 1;
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
	waiting_client(serv, env, server_fd, &address);
}
