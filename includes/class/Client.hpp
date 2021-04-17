#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "../../libft-cpp/include/libft.hpp"
#include "../../libft-cpp/include/get_next_line.hpp"

#include "Request.hpp"
#include "Response.hpp"

class Client {
    public:
		Client();
		Client(const Client &other);
		~Client();
		Client &operator=(const Client &other);
		Client(int socket);

		void	setRequest(Request *value);
		void	setSocket(int value);
		void	setTimeout(int value);
		void	setDir(std::string value);
		void	setRecvEnd(int value);
		Request	*getRequest() const;
		int	getSocket() const;
		int	getTimeout() const;
		std::string getDir() const;
		int	getRecvEnd() const;

	private:
		Request *_req;
		int _socket;
		std::string _dir;
		int _recvEnd;
		int _timeout;
};

#endif // !REQUEST_HPP