#include "global.hpp"

int		config_data_serv(Server serv, int server_fd, int new_socket, int fd_opt)
{
	int request_fd;
	char *dataserv = ft_strjoin("./server/dataServ/", serv.getServerName().c_str());
	struct stat st;

	if (!dataserv)
		exit_err("malloc failed", NULL, new_socket, server_fd);
	if (stat("./server/dataServ", &st) == -1)
		if (mkdir("./server/dataServ", 0700) == -1)
			exit_err("mkdir failed", dataserv, new_socket, server_fd);
	if ((request_fd = open(dataserv, fd_opt, 0644)) < 0)
		exit_err("open failed", dataserv, new_socket, server_fd);
	free(dataserv);
	return (request_fd);
}

void	one_client(Server serv, char **env, int new_socket, int server_fd)
{
	int request_fd;
	char buffer[RECV_BUFF];
	ft_bzero(buffer, RECV_BUFF);
	if ((request_fd = config_data_serv(serv, server_fd, new_socket, O_CREAT | O_WRONLY | O_TRUNC)) >= 0)
	{
		while(recv(new_socket, buffer, RECV_BUFF - 1, 0) > 0)
		{
			write(request_fd, buffer, ft_strlen(buffer));
			ft_bzero(buffer, RECV_BUFF - 1);
		}
		close(request_fd);
		if ((request_fd = config_data_serv(serv, server_fd, new_socket, O_RDONLY)) >= 0)
		{
			Request req;
			try
			{
				req.config_request(request_fd);
				Response res;
				res.config_response();
				if (send(new_socket, res.getResponse().c_str(), ft_strlen(res.getResponse().c_str()), 0) < 0)
					std::cout << "\033[1;31m   Error: \033[0;31m send failed\033[0m" << std::endl;
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
			(void)env;
		}
	}
	close(new_socket);
}