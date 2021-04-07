#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#define FALSE 0
#define TRUE 1
#define RECV_BUFF 40000

#include <unistd.h> 
#include <stdio.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <vector>
#include <list>
#include <map>

#include "../libft-cpp/include/libft.hpp"
#include "../libft-cpp/include/get_next_line.hpp"
#include "includes.hpp"

#include "class/Server.hpp"
#include "class/Request.hpp"
#include "class/Response.hpp"
#include "class/Client.hpp"

#endif