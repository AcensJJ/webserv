#include "global.hpp"

int		config_data_serv(Server serv, int server_fd, sockaddr_in *address, int new_socket, char *buffer)
{
	std::cout << std::endl;
	int request_fd;
	char *dataserv = ft_strjoin("./dataServ/", serv.getServerName().c_str());
	if (!dataserv)
	{
		close(new_socket);
		close(server_fd);
		std::cout << "\033[1;31m   Error: \033[0;31m malloc failed\033[0m" << std::endl;
		exit(EXIT_FAILURE);
	}
	if ((request_fd = open(dataserv, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
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

int		accept_one_client(Server serv, int server_fd, sockaddr_in *address)
{
	int new_socket;
	int addrlen = sizeof(address);

	if ((new_socket = accept(server_fd, (struct sockaddr *)address, (socklen_t*)&addrlen)) < 0) 
		std::cout << "\033[1;31m   Error: \033[0;31m accept failed\033[0m" << std::endl; 
	else
		std::cout << "\033[1;32m   Connection: \033[0m accepted" << std::endl;
	if (fcntl(new_socket, F_SETFL, O_NONBLOCK) < 0) 
		std::cout << "\033[1;31m   Error: \033[0;31m fcntl failed\033[0m" << std::endl;
	return (new_socket);
}

void	waiting_client(Server serv, char **env, int server_fd, sockaddr_in *address)
{
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	while (select(server_fd + 1, NULL, NULL, NULL, &timeout) >= 0)
	{
		std::cout << std::endl << "\033[0;34m   WAITING...\033[0m" << std::endl;
		int new_socket;
		if ((new_socket = accept_one_client(serv, server_fd, address)) > 0)
		{
			int request_fd;
			char buffer[1024];
			if ((request_fd = config_data_serv(serv, server_fd, address, new_socket, buffer)) > 0)
			{
				while(recv(new_socket, buffer, 1024, 0) > 0)
				{
					std::cout << buffer;
					write(request_fd, buffer, ft_strlen(buffer));
				}
				close(request_fd);
				std::cout << std::endl;
				// if (send(new_socket, buffer, ft_strlen(buffer), 0) < 0)
				// 	std::cout << "\033[1;31m   Error: \033[0;31m send failed\033[0m" << std::endl;
			}
			close(new_socket);
			std::cout << std::endl;
		}
	}
	std::cout << "\033[1;31m   Error: \033[0;31m select failed\033[0m" << std::endl;
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

int		main(int ac, char **av, char **env)
{
	std::cout << "\033[1;33m   Program starting\033[0m " << std::endl;
	std::vector<Server> *all = new std::vector<Server>;
	std::string str = "./server/conf/server.conf";
	if (ac > 1)
		str = av[1];
	std::cout << std::endl << "\033[1;34m   Parsing file:\033[0m " << str << std::endl;
	if (parse_conf(str.c_str(), all))
		return (-1);
	pid_t pid;
	for (std::vector<Server>::iterator itr = all->begin(); itr != all->end(); itr++)
	{
		Server serv = *itr;
		std::cout << std::endl << "\033[0;35m   New serv:\033[0m " << serv.getServerName() << std::endl;
		if (serv.check_config())
			exit(EXIT_FAILURE);
		else
			launch_serv(serv, env);
	}
    return (EXIT_SUCCESS);
}