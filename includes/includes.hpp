#ifndef INCLUDES_HPP
#define INCLUDES_HPP

class Request;
class Response;
class Client;
class Server;

/***
 *** server_data.cpp
***/
void 	check_end_file(Response *res, int i);
void	one_client_read(Response *res, int i);
void	one_client_send(Response *res, int i, char **env);

/***
 *** server_fnct.cpp
***/
int		exit_err(char *freevar, int new_socket, int server_fd);
int		waiting_client(char **env, Response *res);
int		launch_serv(Response *res);

/***
 *** server_parse_conf.cpp
***/
int		parse_conf(const char *path, std::vector<Server> *all);
#endif