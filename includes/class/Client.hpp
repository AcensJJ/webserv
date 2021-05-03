#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <netinet/in.h>
#include "../../libft-cpp/include/libft.hpp"
#include "../../libft-cpp/include/get_next_line.hpp"

#include "Request.hpp"

class Client {
    public:
		Client();
		Client(const Client &other);
		~Client();
		Client &operator=(const Client &other);
		Client(int socket);

		void		setRequest(Request *value);
		void		setSocket(int value);
		void		setTimeout(int value);
		void		setTime(int value);
		void		setDir(std::string value);
		void		setRecvEnd(int value);
		void		setAddress(sockaddr_in value);
		Request		*getRequest() const;
		int			getSocket() const;
		int			getTimeout() const;
		int			getTime() const;
		std::string getDir() const;
		int			getRecvEnd() const;
		sockaddr_in	getAddress() const;
		
		//Authentification
		void		setLogin();
		std::string getLogin() const;

	private:
		Request		*_req;
		int			_socket, _timeout, _recvEnd;
		std::string	_dir;
		sockaddr_in	_address;
		std::string	_login;
		int			_time;
};

#endif // !REQUEST_HPP