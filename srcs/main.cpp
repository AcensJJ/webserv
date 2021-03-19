#include "global.hpp"

void	waiting_screen()
{
	std::cout  << std::endl << std::endl << "\033[0;34m   WAITING.\033[0m" << std::endl;
	usleep(500000);
	std::cout  <<  "\x1b[A\033\033[0;34m   WAITING..\033[0m" << std::endl;
	usleep(500000);
	std::cout  <<  "\x1b[A\033\033[0;34m   WAITING...\033[0m" << std::endl;
}

int		main(int ac, char **av)
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
		try
		{
			serv.check_config();
			std::vector<Server>::iterator itrcheck = itr;
			while (all->begin() != itr && ++itrcheck != all->begin())
				if (!ft_strcmp(serv.getServerName().c_str(), itrcheck->getServerName().c_str()))
					throw Server::SameServerNameException();
			launch_serv(serv);
		}
		catch (std::exception & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
    return (EXIT_SUCCESS);
}