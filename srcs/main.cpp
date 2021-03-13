#include "global.hpp"

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
	if (RECV_BUFF <= 1)
	{
		std::cout << "\033[1;31m   Error: \033[0;31m RECV_BUFF bad value (\033[0;37m" << RECV_BUFF << "\033[0;31m)\033[0m" << std::endl;
		return (-1);
	}
	if (ac > 1)
		str = av[1];
	std::cout << std::endl << "\033[1;34m   Parsing file:\033[0m " << str << std::endl;
	if (parse_conf(str.c_str(), all))
		return (-1);
	for (std::vector<Server>::iterator itr = all->begin(); itr != all->end(); itr++)
	{
		Server serv(*itr);
		std::cout << std::endl << "\033[0;35m   New serv:\033[0m " << serv.getServerName() << std::endl;
		int err(0);
		try
		{ 
			serv.check_config();
		}
		catch (std::exception & e)
		{
			std::cerr << e.what() << std::endl;
			err++;
		}
		if (!err) launch_serv(serv, env);
	}
    return (EXIT_SUCCESS);
}