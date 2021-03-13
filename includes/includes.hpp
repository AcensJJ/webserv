#ifndef INCLUDES
#define INCLUDES

class Server;

/***
 *** server_fnct.cpp
***/
void	waiting_screen();
int		config_data_serv(Server serv, int server_fd, int new_socket, int fd_opt);
int		accept_one_client(int server_fd, sockaddr_in *address);
void	waiting_client(Server serv, char **env, int server_fd, sockaddr_in *address);

/***
 *** server_recv.cpp
***/
void	one_client(Server serv, char **env, int new_socket, int server_fd);

/***
 *** parse_serv_conf.cpp
***/
int		parse_conf(const char *path, std::vector<Server> *all);

#endif