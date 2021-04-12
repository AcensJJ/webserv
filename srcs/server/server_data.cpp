#include "global.hpp"

int		config_data_serv(Server serv, int server_fd, int new_socket, int fd_opt, fd_set *readfds)
{
	int request_fd;
	char *dataserv = ft_strjoin("./server/dataServ/", serv.getServerName().c_str());
	struct stat st;

	if (!dataserv)
	{
		FD_CLR(server_fd, readfds);
		exit_err("malloc failed", NULL, new_socket, server_fd);
	}
	if (stat("./server/dataServ", &st) == -1)
		if (mkdir("./server/dataServ", 0700) == -1)
		{
			FD_CLR(server_fd, readfds);
			exit_err("mkdir failed", dataserv, new_socket, server_fd);
		}
	if ((request_fd = open(dataserv, fd_opt, 0644)) < 0)
	{
		FD_CLR(server_fd, readfds);
		exit_err("open failed", dataserv, new_socket, server_fd);
	}
	free(dataserv);
	return (request_fd);
}

void	one_client(Server serv, int new_socket, int server_fd, fd_set *readfds, Request *req)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	int timeout(0);
	int request_fd = -1, nbytes = RECV_BUFF - 1;
	char buffer[RECV_BUFF];
	ft_bzero(buffer, RECV_BUFF);
	while(!timeout && nbytes == (RECV_BUFF - 1) && (nbytes = recv(new_socket, (void*)buffer, RECV_BUFF - 1, MSG_DONTWAIT)) > 0)
		if (nbytes > 0)
		{
			gettimeofday(&time, NULL);
			if (time.tv_sec - req->getTime() > 30) timeout = 1;
			if (request_fd == -1) request_fd = config_data_serv(serv, server_fd, new_socket, O_CREAT | O_WRONLY | O_TRUNC, readfds);
			write(request_fd, buffer, nbytes);
		}
	if (timeout)
	{
		try
		{
			Response res;
			res.config_response(req, &serv);
			ssize_t len = 0;
			if ((len = send(new_socket, res.getResponse().c_str(),res.getResponse().length(), 0)) < 0)
				std::cout << "\033[1;31m   Error: \033[0;31m send failed\033[0m" << std::endl;
			std::cout << "Len is |" << len << "|\n";
			throw "Timeout request!";
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	else if (request_fd != -1) 
	{
		close(request_fd);
		if ((request_fd = config_data_serv(serv, server_fd, new_socket, O_RDONLY, readfds)) >= 0)
		{
			try
			{
				req->config_request(request_fd);
				Response res;
				res.config_response(req, &serv);
				ssize_t len2 = 0;
				if ((len2 = send(new_socket, res.getResponse().c_str(), res.getResponse().length(), 0)) < 0)
					std::cout << "\033[1;31m   Error: \033[0;31m send failed\033[0m" << std::endl;
				std::cout << "Len2 is |" << len2 << "|\n";
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
	}
}