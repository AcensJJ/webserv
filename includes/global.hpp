#ifndef GLOBAL
#define GLOBAL

#define FALSE 0
#define TRUE 1
#include "Server.hpp"

int		parse_conf(const char *path, std::vector<Server> *all);
#endif