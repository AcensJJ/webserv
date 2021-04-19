#include "global.hpp"

static int remove_directory(const char *path)
{
	DIR *d = opendir(path);
	size_t path_len = ft_strlen(path);
	int r = -1;

	if (d)
	{
		struct dirent *p;

		r = 0;
		while (!r && (p=readdir(d))) 
		{
			int r2 = -1;
			std::string buf;
			size_t len;

			/* Skip the names "." and ".." as we don't want to recurse on them. */
			if (!ft_strcmp(p->d_name, ".") || !ft_strcmp(p->d_name, ".."))
				continue;

			len = path_len + ft_strlen(p->d_name) + 2;
			struct stat statbuf;
			buf = path;
			buf.push_back('/');
			buf.insert(buf.length(), p->d_name);
			if (!stat(buf.c_str(), &statbuf)) 
			{
				if (S_ISDIR(statbuf.st_mode))
					r2 = remove_directory(buf.c_str());
				else
					r2 = unlink(buf.c_str());
			}
			r = r2;
		}
		closedir(d);
	}
	if (!r)
		r = rmdir(path);
	return (r);
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
	remove_directory(DATA_SERV);
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