#ifndef GLOBAL
#define GLOBAL

#define FALSE 0
#define TRUE 1
#define RECV_BUFF 1024

#include <unistd.h> 
#include <stdio.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string>
#include <sys/types.h>
#include <arpa/inet.h>

#include "../libft-cpp/include/libft.hpp"
#include "../libft-cpp/include/get_next_line.hpp"
#include "includes.hpp"

#include "class/Server.hpp"

#endif