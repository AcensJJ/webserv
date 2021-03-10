#include "global.hpp"

void	running_serv(Server serv, char **env, int server_fd, sockaddr_in address)
{
	struct timeval timeout;
	int addrlen = sizeof(address);
	fd_set set;
	FD_ZERO(&set);
	FD_SET(server_fd, &set);
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	while (select(server_fd + 1, &set, NULL, NULL, &timeout) >= 0)
	{
		int new_socket;
		std::cout << "\033[0;34m   WAITING...\033[0m" << std::endl;
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) 
		{
			close(server_fd);
			std::cout << "\033[1;31m   Error: \033[0;31m accept\033[0m" << std::endl;
			exit(EXIT_FAILURE);
		}
		// recv + fcntl O_NONBLOCK

		// send

		std::cout << new_socket << std::endl;
		std::cout << server_fd << std::endl;
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
	// address.sin_addr.s_addr = INADDR_ANY;
	if (strcmp(serv._host.c_str(), "localhost"))
		address.sin_addr.s_addr = inet_addr(serv._host.c_str());
	else
		address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons( serv._port );
	std::cout << serv._host << std::endl;
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
	std::cout << "\033[1;32m   Server launch succesly: \033[0;36mhttp://localhost:" << serv._port << "\033[0m" << std::endl;
	running_serv(serv, env, server_fd, address);
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
		if ((pid = fork()) == -1)
		{
			std::cout << "fork error" << std::endl;
			return (-1);
		}
		else if (pid == 0) {
			Server serv = *itr;
			std::cout << std::endl << "\033[0;35m   New serv:\033[0m " << serv._server_name << std::endl;
			if (serv.check_config())
				exit(EXIT_FAILURE);
			else
				launch_serv(serv, env);
		}
	}
	waitpid(pid, NULL, 0);
    return (EXIT_SUCCESS);
}