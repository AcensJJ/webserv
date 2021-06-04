#include "global.hpp"

void check_end_file(Response *res, int i)
{
	if (!res->getClient()[i]->getBodyToWork())
	{
		std::ifstream fs(res->getClient()[i]->getDir());
		if (fs.is_open())
		{
			std::stringstream ss;
			ss << fs.rdbuf();
			fs.close();
			std::string check = ss.str();
			size_t j;
			if ((j = check.find("\r\n\r\n")) != std::string::npos)
			{
				std::string tmp = &check[j + 4];
				if (check.find("Transfer-Encoding:") != std::string::npos && check.find("chunked") != std::string::npos)
				{
					res->getClient()[i]->setBodyToWork(true);
					res->getClient()[i]->setMsg(tmp);
				}
				else if ((j = check.find("Content-Length:")) != std::string::npos)
				{
					int nb = ft_atoi(&check[j + 16]);
					if ((size_t)nb <= tmp.length())
					{
						res->getClient()[i]->setBodyToWork(true);
						res->getClient()[i]->setRecvEnd(true);
						res->getClient()[i]->setMsg(tmp);
					}
				}
				else if (check.find("\r\n") != std::string::npos) res->getClient()[i]->setRecvEnd(true);
			}
		}
	}
	else 
	{
		int stop = 0;
		while (!res->getClient()[i]->getRecvEnd() && !res->getClient()[i]->getMsg().empty() && !stop)
		{
			if (res->getClient()[i]->getSize() == -1 && res->getClient()[i]->getMsg().find("\r\n") != std::string::npos)
			{
				res->getClient()[i]->setSize(ft_atoi_base((char *)res->getClient()[i]->getMsg().c_str(), (char *)"0123456789abcdef\0"));
				int k = 0;
				while (!res->getClient()[i]->getMsg().empty() && ((res->getClient()[i]->getMsg()[k] >= '0' && res->getClient()[i]->getMsg()[k] <= '9') || (res->getClient()[i]->getMsg()[k] >= 'a' && res->getClient()[i]->getMsg()[k] <= 'f')))
					k++;
				res->getClient()[i]->setMsg(&res->getClient()[i]->getMsg()[k + 2]);
			}
			if (res->getClient()[i]->getSize() != -1)
			{
				if (res->getClient()[i]->getSize() == 0)
					res->getClient()[i]->setRecvEnd(true);
				else if ((size_t)(res->getClient()[i]->getSize() + 2) < res->getClient()[i]->getMsg().length())
				{
					std::string msg;
					msg = res->getClient()[i]->getMsg().substr(0, res->getClient()[i]->getSize());
					res->getClient()[i]->setMsg(&res->getClient()[i]->getMsg()[res->getClient()[i]->getSize() + 2]);
					if (!msg.empty()) res->getClient()[i]->_chunck.push_back(msg);
					res->getClient()[i]->setSize(-1);
				}
				else stop = 1;
			}
			else stop = 1;
		}
	}
}

static int	config_data_serv(Response *res, int i, int fd_opt)
{
	int request_fd;
	struct stat st;
	if (stat(DATA_SERV, &st) == -1)
		if (mkdir(DATA_SERV, 0700) == -1){
			delete res->getClient()[i];
			res->getClient()[i] = NULL;
			return (-1);
		}
	if (res->getClient()[i]->getDir().empty())
	{
		std::string dataserv = DATA_SERV;
		dataserv.insert(dataserv.length(), res->getServer()->getServerName().c_str());
		dataserv.insert(dataserv.length(), "_");	
		char *nb = ft_itoa(res->getClient()[i]->getSocket());
		if (!nb){
			delete res->getClient()[i];
			res->getClient()[i] = NULL;
			return (-1);
		}
		dataserv.insert(dataserv.length(), nb);
		free(nb);
		res->getClient()[i]->setDir(dataserv);
		if ((request_fd = open(res->getClient()[i]->getDir().c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0){
			delete res->getClient()[i];
			res->getClient()[i] = NULL;
			return (-1);
		}
		close(request_fd);
	}
	if ((request_fd = open(res->getClient()[i]->getDir().c_str(), fd_opt, 0644)) < 0){
		delete res->getClient()[i];
		res->getClient()[i] = NULL;
		return (-1);
	}
	return (request_fd);
}

void	one_client_read(Response* res, int i)
{
	struct timeval time;
	int request_fd, nbytes = RECV_BUFF - 1;
	char buffer[RECV_BUFF];
	ft_bzero((void *)buffer, RECV_BUFF);
	nbytes = recv(res->getClient()[i]->getSocket(), (void*)buffer, RECV_BUFF - 1, MSG_DONTWAIT);
	if (nbytes > 0)
	{
		gettimeofday(&time, NULL);
		if (time.tv_sec - res->getClient()[i]->getTime() > TIMEOUT) res->getClient()[i]->setTimeout(1);
		if (!res->getClient()[i]->getBodyToWork())
		{
			request_fd = config_data_serv(res, i, O_CREAT | O_WRONLY | O_APPEND);
			write(request_fd, buffer, nbytes);
			close(request_fd);
		}
		else {
			buffer[nbytes] = '\0';
			res->getClient()[i]->setMsg(res->getClient()[i]->getMsg() + buffer);
		}

	}
	if (nbytes == -1) {
		delete res->getClient()[i];
		res->getClient()[i] = NULL;	
	}
}

void	one_client_send(Response *res, int i, char **env)
{
	try
	{
		std::cout << std::endl << "\033[0;33m   Working on socket\033[0m(" << res->getClient()[i]->getSocket() << ")" << std::endl;
		res->getRequest()->setTime(res->getClient()[i]->getTime());
		res->getRequest()->config_request(res->getClient()[i]->getDir());
		res->config_response(env, i);
		if (send(res->getClient()[i]->getSocket(), res->getResponse().c_str(), res->getResponse().length(), 0) < 0)
		{
			std::cerr << "\033[1;31m   Error: \033[0;31m send failed\033[0m" << std::endl;
		}
		res->clear();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

}
