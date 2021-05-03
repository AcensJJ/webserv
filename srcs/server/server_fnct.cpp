#include "global.hpp"

void		exit_err(std::string err, char *freevar, int new_socket, int server_fd)
{
	if (freevar) free(freevar);
	if (new_socket > -1) close(new_socket);
	if (server_fd > -1) close(server_fd);
	std::cout << "\033[1;31m   Error: \033[0;31m " << err << "\033[0m" << std::endl;
	exit(EXIT_FAILURE);
}

static int	accept_one_client(int server_fd, sockaddr_in *address)
{
	int new_socket, addrlen = sizeof(address);
	std::cout << std::endl << "\033[1;33m   Waiting: \033[0;33m trying to accept one client\033[0m" << std::endl; 
	if ((new_socket = accept(server_fd, (struct sockaddr *)address, (socklen_t*)&addrlen)) < 0) 
		std::cout << "\033[1;31m   Error: \033[0;31m accept failed\033[0m" << std::endl; 
	else
		fcntl(new_socket, F_SETFL, O_NONBLOCK);
	return (new_socket);
}

static void config_client(fd_set *readfds, fd_set *writefds, int fd)
{
	FD_ZERO(readfds);
	FD_SET(fd, readfds);
	FD_ZERO(writefds);
	FD_SET(fd, writefds);
}

static void	waiting_client(Server serv, int server_fd, sockaddr_in address, char **env)
{
	fd_set readfds, writefds, rfd, wfd;
	config_client(&readfds, &writefds, server_fd);
	rfd = readfds;
	wfd = writefds;
	Client *allclient[FD_SETSIZE];
	for (int i = 1; i < FD_SETSIZE; i++)
		allclient[i] = NULL;
	while (select(FD_SETSIZE, &rfd, &wfd, NULL, NULL) > 0)
	{
		int new_socket;
		for (int i = 1; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &rfd)) 
			{
				if (i == server_fd)
				{
					if ((new_socket = accept_one_client(server_fd, &address)) >= 0)
					{
						FD_SET(new_socket, &readfds);
						FD_SET(new_socket, &writefds);
						allclient[new_socket] = new Client(new_socket);
						allclient[new_socket]->setAddress(address);
						std::cout << "\033[1;35m   new Connection:\033[0m client (" << new_socket << ") accepted \033[0m" << std::endl;
					}
				}
				else if (allclient[i] && !allclient[i]->getRecvEnd())
					one_client_read(serv, &readfds, &writefds, allclient[i], allclient);
			}
			if (FD_ISSET(i, &wfd))
			{
				if (allclient[i] && allclient[i]->getRecvEnd() == 1)
				{
					one_client_send(serv, &readfds, &writefds, allclient[i], allclient, env);
					FD_CLR(i, &readfds);
					FD_CLR(i, &writefds);
					close(i);
					unlink(allclient[i]->getDir().c_str());
					close(allclient[i]->getSocket());
					delete allclient[i];
					allclient[i] = NULL;
					std::cout << "\033[1;32m   Connection:\033[0m closed for (" << i << ")" << std::endl;
				}
			}
		}
		rfd = readfds;
		wfd = writefds;
	}
	for (int i = 1; i < FD_SETSIZE; i++)
	{
		if (allclient[i]) 
		{
			delete allclient[i];
			allclient[i] = NULL;
		}
		FD_CLR(i, &readfds);
		FD_CLR(i, &writefds);
		close(i);
	}
	exit_err("select failed", NULL, -1, -1);
}

void		launch_serv(Server serv, char **env)
{
	int server_fd, opt = 1;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) exit_err("socket failed", NULL, -1, -1);
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) exit_err("setsockopt failed", NULL, -1, server_fd);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	if (ft_strcmp(serv.getHost().c_str(), "localhost"))
		address.sin_addr.s_addr = inet_addr(serv.getHost().c_str());
	else
		address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons( serv.getPort() );
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))) exit_err("bind failed", NULL, -1, server_fd);
	if (listen(server_fd, 128)) exit_err("listen failed", NULL, -1, server_fd);
	std::cout << "\033[1;32m   Server launch succesly: \033[0;36mhttp://localhost:" << serv.getPort() << "\033[0m" << std::endl;
	waiting_client(serv, server_fd, address, env);
}
