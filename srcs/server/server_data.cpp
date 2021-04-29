#include "global.hpp"

static void	clear_exit(Client *allclient[FD_SETSIZE], fd_set *readfds, fd_set *writefds, std::string msg)
{
	for (int i = 1; i < FD_SETSIZE; i++)
	{
		if (allclient[i]) 
		{
			delete allclient[i];
			allclient[i] = NULL;
		}
		FD_CLR(i, readfds);
		FD_CLR(i, writefds);
		close(i);
	}
	exit_err(msg, NULL, -1, -1);
}

static int	config_data_serv(Server serv, Client *client, int fd_opt, fd_set *readfds, fd_set *writefds, Client *allclient[FD_SETSIZE])
{
	int request_fd;
	struct stat st;
	if (stat("./server/dataServ", &st) == -1)
		if (mkdir("./server/dataServ", 0700) == -1)
			clear_exit(allclient, readfds, writefds, "mkdir failed");
	if (client->getDir().empty())
	{
		std::string dataserv = DATA_SERV;
		dataserv.insert(dataserv.length(), serv.getServerName().c_str());
		dataserv.insert(dataserv.length(), "_");	
		char *nb = ft_itoa(client->getSocket());
		if (!nb) clear_exit(allclient, readfds, writefds, "malloc failed");
		dataserv.insert(dataserv.length(), nb);
		free(nb);
		client->setDir(dataserv);
		if ((request_fd = open(client->getDir().c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
			clear_exit(allclient, readfds, writefds, "open failed");
		close(request_fd);
	}
	if ((request_fd = open(client->getDir().c_str(), fd_opt, 0644)) < 0)
		clear_exit(allclient, readfds, writefds, "open failed");
	return (request_fd);
}

void	one_client_read(Server serv, fd_set *readfds, fd_set *writefds, Client *client, Client *allclient[FD_SETSIZE])
{
	struct timeval time;
	gettimeofday(&time, NULL);
	int request_fd, nbytes = RECV_BUFF - 1;
	char buffer[RECV_BUFF];
	nbytes = recv(client->getSocket(), (void*)buffer, RECV_BUFF - 1, MSG_DONTWAIT);
	if (nbytes > 0)
	{
		gettimeofday(&time, NULL);
		if (time.tv_sec - client->getRequest()->getTime() > TIMEOUT) client->setTimeout(1);
	std::cout << client->getRequest()->getTime() << " : one client_read BAD\n";

		request_fd = config_data_serv(serv, client, O_CREAT | O_WRONLY | O_APPEND, readfds, writefds, allclient);
		write(request_fd, buffer, nbytes);
		close(request_fd);
		if (nbytes != RECV_BUFF - 1) client->setRecvEnd(1);
	}
}

void	one_client_send(Server serv, fd_set *readfds, fd_set *writefds, Client *client, Client *allclient[FD_SETSIZE], char **env)
{
	int request_fd = config_data_serv(serv, client, O_RDONLY, readfds, writefds, allclient);
	try
	{
		std::cout << std::endl << "\033[0;33m   Working on socket\033[0m(" << client->getSocket() << ")" << std::endl;
		Response res;
		Request req = *client->getRequest();
		req.setTime(client->getRequest()->getTime());
	std::cout << client->getRequest()->getTime() << " : one clientsend wtf BAD\n";

		client->setRequest(&req);
		client->getRequest()->config_request(request_fd);
		res.config_response(&req, &serv, env, client);
		if (send(client->getSocket(), res.getResponse().c_str(), res.getResponse().length(), 0) < 0)
			throw "\033[1;31m   Error: \033[0;31m send failed\033[0m";
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	close(request_fd);
}
