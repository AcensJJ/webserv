#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#define FALSE 0
#define TRUE 1
#define RECV_BUFF 40001
#define TIMEOUT 500
#define SERV_WWW "./server/www/"
#define DATA_SERV "./server/dataServ/"

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
#include <dirent.h>
#include <algorithm>

#include "../libft-cpp/include/libft.hpp"
#include "../libft-cpp/include/get_next_line.hpp"
#include "includes.hpp"

#include "class/Routes.hpp"
#include "class/Server.hpp"
#include "class/Request.hpp"
#include "class/Response.hpp"
#include "class/Client.hpp"

#endif