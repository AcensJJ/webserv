#include "global.hpp"

// void	launch_serv(Server serv, char **env)
// {

// }

int		main(int ac, char **av, char **env)
{
	std::vector<Server> *all = new std::vector<Server>;
	std::string str = "./server/conf/server.conf";
	pid_t pid;
    off_t ble;
	if (ac > 1)
		str = av[1];
	if (parse_conf(str.c_str(), all))
		return (-1);
	for (std::vector<Server>::iterator itr = all->begin(); itr != all->end(); itr++)
	{
		if ((pid = fork()) == -1)
		{
			std::cout << "fork error" << std::endl;
			return (-1);
		}
		else if (pid == 0) {
			Server serv = *itr;
			// launch_serv(serv, env);
		}
	}
	waitpid(pid, NULL, 0);
    return (EXIT_SUCCESS);
}