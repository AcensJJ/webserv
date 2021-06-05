#include "global.hpp"

int		exit_err(char *freevar, int new_socket, int server_fd)
{
	if (freevar) free(freevar);
	if (new_socket > -1) close(new_socket);
	if (server_fd > -1) close(server_fd);
	return (-1);
}

static int	accept_one_client(int server_fd, sockaddr_in address)
{
	int new_socket, addrlen = sizeof(&address);
	std::cout << std::endl << "\033[1;33m   Waiting: \033[0;33m trying to accept one client\033[0m" << std::endl; 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) 
		std::cout << "\033[1;31m   Error: \033[0;31m accept failed\033[0m" << std::endl; 
	else
		fcntl(new_socket, F_SETFL, O_NONBLOCK);
	return (new_socket);
}

int			waiting_client(char **env, Response *res)
{
	fd_set rfd, wfd;
	rfd = *res->getServer()->getRdFdAddr();
	wfd = *res->getServer()->getWrFdAddr();
	if (select(FD_SETSIZE, &rfd, &wfd, NULL, NULL) > 0)
	{
		for (int i = 1; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &rfd)) 
			{
				if (i == res->getServer()->getSocket())
				{
					int new_socket;
					if ((new_socket = accept_one_client(res->getServer()->getSocket(), res->getServer()->getSockAddr())) >= 0)
					{
						FD_SET(new_socket, res->getServer()->getRdFdAddr());
						FD_SET(new_socket, res->getServer()->getWrFdAddr());
						res->getClient()[new_socket] = new Client(new_socket);
						res->getClient()[new_socket]->setAddress(res->getServer()->getSockAddr());
						std::cout << "\033[1;35m   new Connection:\033[0m client (" << new_socket << ") accepted on server [" << res->getServer()->getServerName() << "]" << std::endl;
					}
				}
				else if (res->getClient()[i])
				{
					check_end_file(res, i);
					if (!res->getClient()[i]->getRecvEnd())
						one_client_read(res, i);
				}
			}
			else if (FD_ISSET(i, &wfd))
			{
				if (res->getClient()[i] && res->getClient()[i]->getRecvEnd() == 0) check_end_file(res, i);
				if (res->getClient()[i] && res->getClient()[i]->getRecvEnd() == 1)
				{
					one_client_send(res, i, env);
					if (res->getClient()[i]->getResponse().length() == res->getClient()[i]->getPos())
					{
						FD_CLR(i, res->getServer()->getRdFdAddr());
						FD_CLR(i, res->getServer()->getWrFdAddr());
						close(i);
						unlink(res->getClient()[i]->getDir().c_str());
						delete res->getClient()[i];
						res->getClient()[i] = NULL;
						std::cout << "\033[1;32m   Connection:\033[0m closed for (" << i << ") on server [" << res->getServer()->getServerName() << "]" << std::endl;
					}
				}
			}
		}
	}
	return (0);
}

int		launch_serv(Response *res)
{
	int server_fd, opt = 1;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) return (exit_err(NULL, -1, -1));
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) return (exit_err(NULL, -1, server_fd));
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	if (ft_strcmp(res->getServer()->getHost().c_str(), "localhost"))
		address.sin_addr.s_addr = inet_addr(res->getServer()->getHost().c_str());
	else
		address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons( res->getServer()->getPort() );
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))) return (exit_err(NULL, -1, server_fd));
	if (listen(server_fd, 128)) return (exit_err(NULL, -1, server_fd));
	res->getServer()->setSocket(server_fd);
	res->getServer()->setSockAddr(address);
	std::cout << "\033[1;32m   Server launch succesfully \033[0m[" << res->getServer()->getServerName() << "]\033[1;32m:  \033[0;36mhttp://localhost:" << res->getServer()->getPort() << "\033[0m" << std::endl;
	return (0);
}
