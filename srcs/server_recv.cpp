#include "global.hpp"

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
			// Request req;
			// try
			// {
			// 	req.config_request(reques_fd);
			// }
			// catch(const std::exception& e)
			// {
			// 	std::cerr << e.what() << std::endl;
			// }
			
			// if (send(new_socket, buffer, ft_strlen(buffer), 0) < 0)
			// 	std::cout << "\033[1;31m   Error: \033[0;31m send failed\033[0m" << std::endl;
			(void)env;
		}
	}
	close(new_socket);
}