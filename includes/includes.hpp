#ifndef INCLUDES_HPP
#define INCLUDES_HPP

class Server;
class Request;

/***
 *** server_data.cpp
***/
int		config_data_serv(Server serv, int server_fd, int new_socket, int fd_opt, fd_set *readfds);
void	one_client(Server serv, int new_socket, int server_fd, fd_set *readfds, Request *req);

/***
 *** server_fnct.cpp
***/
void	exit_err(std::string err, char *freevar, int new_socket, int server_fd);
int		accept_one_client(int server_fd, sockaddr_in *address);
void	waiting_client(Server serv, int server_fd, sockaddr_in *address);
void	launch_serv(Server serv);

/***
 *** server_parse_conf.cpp
***/
int		parse_conf(const char *path, std::vector<Server> *all);
#endif