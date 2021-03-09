#ifndef GLOBAL
#define GLOBAL

#define FALSE 0
#define TRUE 1

#include <unistd.h> 
#include <stdio.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string>
#include <sys/types.h>

#include "Server.hpp"

int		parse_conf(const char *path, std::vector<Server> *all);
#endif