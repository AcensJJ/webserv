#ifndef INCLUDES_HPP
#define INCLUDES_HPP

class Server;
class Request;
class Client;

/***
 *** server_data.cpp
***/
void	one_client_read(Server serv, fd_set *readfds, fd_set *writefds, Client *client, Client *allclient[FD_SETSIZE]);
void	one_client_send(Server serv, fd_set *readfds, fd_set *writefds, Client *client, Client *allclient[FD_SETSIZE], char **env);

/***
 *** server_fnct.cpp
***/
void	exit_err(std::string err, char *freevar, int new_socket, int server_fd);
void	launch_serv(Server serv, char **env);

/***
 *** server_parse_conf.cpp
***/
int		parse_conf(const char *path, std::vector<Server> *all);
#endif