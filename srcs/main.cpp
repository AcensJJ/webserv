#include "global.hpp"

void	launch_serv(Server serv, char **env)
{
	if (serv.check_config())
		exit(EXIT_FAILURE);
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cout << "\033[1;31m   Error: \033[0;31msocket failed\033[0m" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Setting value to the socket
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		close(server_fd);
		std::cout << "\033[1;31m   Error: \033[0;31msetsockopt\033[0m" << std::endl;
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( serv._port );
	std::cout << "\033[1;32m   Server launch succesly: \033[0;36mhttp://localhost:" << serv._port << "\033[0m" << std::endl;
	
	// Forcefully attaching socket to the port
	// set local addr
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)))
	{
		std::cout << "error: bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	// reference as an passiv socket
	if (listen(server_fd, 3))
	{
		std::cout << "\033[1;31m   Error: \033[0;31mlisten\033[0m" << std::endl;
		exit(EXIT_FAILURE);
	}

	// extract the first connexion on the waiting line and create a new socker connexion
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) 
	{ 
		std::cout << "\033[1;31m   Error: \033[0;31maccept\033[0m" << std::endl;
		exit(EXIT_FAILURE); 
	} 
	while (1)
	{}
}

int		main(int ac, char **av, char **env)
{
	// setting value and check
	std::cout << "\033[1;33m   Program starting\033[0m " << std::endl;
	std::vector<Server> *all = new std::vector<Server>;
	std::string str = "./server/conf/server.conf";
	if (ac > 1)
		str = av[1];

	// parsing file
	std::cout << std::endl << "\033[1;34m   Parsing file:\033[0m " << str << std::endl;
	if (parse_conf(str.c_str(), all))
		return (-1);

	// foreach all serv
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
			launch_serv(serv, env);}
	}
	waitpid(pid, NULL, 0);
	
    return (EXIT_SUCCESS);
}