#include "global.hpp"

static void	set_server(std::vector<Server> *all)
{
	Server _new;
	all->push_back(_new);
	std::list<Routes> route;
	std::list<std::string> error;
	all->rbegin()->_routes = route;
	all->rbegin()->_error_pages = error;
}

static int		set_listen(std::vector<Server> *all, char **line, int i, int j)
{
	while ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32)
		i++;
	char *add;
	add = &line[j][i];
	char **adds;
	all->rbegin()->setListen(add);
	if (!(adds = ft_split(add, ':')))
	{
		std::cout << "\033[1;31m   Error malloc\033[0m" << std::endl;
		return (1);
	}
	j = 7;
	while ((adds[0][j] >= 9 && adds[0][j] <= 13) || adds[0][j] == 32)
		j++;
	if (adds[0]) all->rbegin()->setHost(&adds[0][j]);
	if (adds[1]) all->rbegin()->setPort(ft_atoi(adds[1]));
	int k(0);
	while (adds[k])
		free(adds[k++]);
	free(adds);
	return (0);
}

static void	set_server_name(std::vector<Server> *all, char **line, int i, int j)
{
	i += 12;
	while ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32)
		i++;
	char *add;
	add = &line[j][i];
	all->rbegin()->setServerName(add);
}

static void	set_limit_client_body(Routes *_new, char **line, int i, int j)
{
	i += 18;
	while ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32)
		i++;
	char *add;
	add = &line[j][i];
	_new->setLimitClientBody(add);
}

static void	set_routes_listen(Routes *_new, char **line, int i, int j)
{
	i += 10;
	i++;
	while (line[j][i] && ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32))
		i++;
	_new->setListen(FALSE);
	if (!ft_strncmp(&line[j][i], "on", 2))
		_new->setListen(TRUE);
}

static void	set_routes_cgi_path(Routes *_new, char **line, int i, int j)
{
	i += 9;
	while ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32)
		i++;
	char *add;
	add = &line[j][i];
	_new->setGCIPath(add);
}

static void	set_routes_location(Routes *_new, char **line, int i, int j)
{
	i += 5;
	while ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32)
		i++;
	char *add;
	add = &line[j][i];
	_new->setLocation(add);
}

static void	set_routes_default(Routes *_new, char **line, int i, int j)
{
	char *add;
	add = &line[j][i];
	_new->setDefault(add);
}

static void	set_error_page(std::vector<Server> *all, char **line, int i, int j)
{
	i += 11;
	while ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32)
		i++;
	char *add;
	add = &line[j][i];
	all->rbegin()->_error_pages.push_back(add);
}

static int		set_location(std::vector<Server> *all, char **line, int i, int j)
{
	i += 9;
	Routes _new;
	int sep;
	std::string str = &line[j][i];
	sep = str.rfind(' ');
	std::string norme = &str[sep];
	if (norme.find("{") == std::string::npos)
	{
		std::cout << "\033[1;31m   Norme error\033[0m" << std::endl;
		return (-1);
	}
	_new.setDirFile(str.substr(0, sep));
	j++;
	i = 0;
	while (line[j] && ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32))
		i++;
	while (line[j] && line[j][i] != '}')
	{
		if (!ft_strncmp(&line[j][i], "GET", 3) || !ft_strncmp(&line[j][i], "HEAD", 4) ||
		!ft_strncmp(&line[j][i], "POST", 4) || !ft_strncmp(&line[j][i], "PUT", 3) ||
		!ft_strncmp(&line[j][i], "DELETE", 6) || !ft_strncmp(&line[j][i], "CONNECT", 6) ||
		!ft_strncmp(&line[j][i], "OPTIONS", 7) || !ft_strncmp(&line[j][i], "TRACE", 5) ||
		!ft_strncmp(&line[j][i], "PATCH", 5))
			_new.setMethod(&line[j][i]);
		if (!ft_strncmp(&line[j][i], "auto_index ", 11))
			set_routes_listen(&_new, line, i, j);
		else if (!ft_strncmp(&line[j][i], "cgi_path ", 9))
			set_routes_cgi_path(&_new, line, i, j);
		else if (!ft_strncmp(&line[j][i], "root ", 5))
			set_routes_location(&_new, line, i, j);
		else if (!strncmp(&line[j][i], "limit_client_body=", 18))
			set_limit_client_body(&_new, line, i, j);
		else
			set_routes_default(&_new, line, i, j);
		j++;
		i = 0;
		while (line[j] && ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32))
			i++;
	}
	i = 0;
	while (line[j] && line[j][i] && line[j][i] != '}')
		i++;
	i++;
	while (line[j] && ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32))
		i++;
	while (line[j] && line[j][i] != '}')
	{
		i = 0;
		j++;
		while (line[j] && line[j][i] && ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32))
			i++;
	}
	all->rbegin()->_routes.push_back(_new);
	if (line[j] && (line[j][i] == '}'))
		return (--j);
	std::cout << "\033[1;31m   Norme error\033[0m" << std::endl;
	return (-1);
}

static int		check_bef_serv(char **line, int j)
{
	int i;
	int skip_empty_line(1);

	while (skip_empty_line)
	{
		j--;
		i = 0;
		while (j >= 0 && line[j] == '\0')
			j--;
		if (j < 0) return (0);
		while (line[j][i])
			i++;
		i--;
		while (i > -1 && line[j][i] && ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32))
			i--;
		if (i > -1)
			skip_empty_line = 0;
	}
	if (line[j][i] != '}')
	{
		std::cout << "\033[1;31m   File is not normed: \033[0;31m missing '}'\033[0m" << std::endl;
		return (-1);
	}
	return (0);
}

static int		check_aft_serv(char **line, int i, int j)
{
	int	parsing(0);

	i+=6;
	while (line[j] && parsing == 0)
	{
		while (line[j][i] && ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32))
			i++;
		if (line[j][i] && line[j][i] == '{')
			parsing++;
		else if (line[j][i] == '\n' || line[j][i] == '\0')
		{
			i = 0;
			j++;
		}
		else
			parsing--;
	}
	if (parsing < 1)
		std::cout << "\033[1;31m   File is not normed: \033[0;31m missing '{'\033[0m" << std::endl;
	return (parsing);
}

static int		set_value(char **line, std::vector<Server> *all)
{
	int j(-1);

	while (line[++j])
	{
		int i(0);
		while (line[j][i] && ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32))
			i++;
		if (!ft_strncmp(&line[j][i], "}", 1))
			while (line[j] && !ft_strncmp(&line[j][i], "server", 6))
			{
				j++;
				i=0;
				while (line[j][i] && ((line[j][i] >= 9 && line[j][i] <= 13) || line[j][i] == 32))
					i++;
			}
		if (!ft_strncmp(&line[j][i], "server", 6))
		{
			if (check_bef_serv(line, j))
				return (-1);
			set_server(all);
			if (check_aft_serv(line, i, j) < 0)
				return (-1);
		}
		else if (!ft_strncmp(&line[j][i], "listen=", 7))
		{
			if (set_listen(all, line, i, j))
				return (-1);
		}
		else if (!ft_strncmp(&line[j][i], "name_server=", 12))
			set_server_name(all, line, i, j);
		else if (!strncmp(&line[j][i], "error_page=", 11))
			set_error_page(all, line, i, j);
		else if (!ft_strncmp(&line[j][i], "location", 8))
			if ((j = set_location(all, line, i, j)) < 0)
				return (-1);
	}
	if (check_bef_serv(line, j) < 0)
		return (-1);
	return (0);
}

int		parse_conf(const char *path, std::vector<Server> *all)
{
	int conf;
	if ((conf = open(path, O_RDONLY)) < 0)
	{
		std::cout << "\033[1;31m   No such file:  \033[0;35m" << path << "\033[0m" << std::endl;
		return (-1);
	}
	unsigned long long nb_line(1);
	char *line;
	while (get_next_line(conf, &line) > 0 && ++nb_line)
		free(line);
	++nb_line;
	if (line) free(line);
	line = NULL;
	close(conf);
	if ((conf = open(path, O_RDONLY)) < 0)
	{
		std::cout << "\033[1;31m   Error: \033[0;31m openning file an 2nd time\033[0m" << std::endl;
		return (-1);
	}
	char **all_line;
	if (!(all_line = (char **)malloc(sizeof(all_line) * nb_line)))
	{
		std::cout << "\033[1;31m   Error: \033[0;31m malloc\033[0m" << std::endl;
		return (-1);
	}
	nb_line = 0;
	while (get_next_line(conf, &line) > 0)
		all_line[nb_line++] = line;
	if (line) all_line[nb_line++] = line;
	all_line[nb_line] = NULL;
	int ret;
	ret = set_value(all_line, all); 
	for (int i = 0; all_line[i]; i++)
		free(all_line[i]);
	free(all_line);
	close(conf);
	return (ret);
}
