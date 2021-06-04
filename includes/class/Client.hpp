#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <netinet/in.h>
#include "../../libft-cpp/include/libft.hpp"
#include "../../libft-cpp/include/get_next_line.hpp"
#include <list>

#include "class/Request.hpp"

class Client {
    public:
		Client();
		Client(const Client &other);
		~Client();
		Client &operator=(const Client &other);
		Client(int socket);

		void		setSocket(int value);
		void		setTimeout(int value);
		void		setTime(int value);
		void		setDir(std::string value);
		void		setRecvEnd(int value);
		void		setAddress(sockaddr_in value);
		void		setBodyToWork(bool value);
		void		setPos(unsigned long long value);
		void		setLength(int value);
		void		setLogin() const;
		void		setMsg(std::string value);
		void		setSize(int value);

		int			getSocket() const;
		int			getTimeout() const;
		int			getTime() const;
		std::string getDir() const;
		int			getRecvEnd() const;
		sockaddr_in	getAddress() const;
		bool		getBodyToWork() const;
		unsigned long long 		getPos() const;
		int			getLength() const;
		std::string getMsg() const;
		int			getSize() const;
		
		//Authentification
		void		setLogin(Request *_req);
		std::string getLogin() const;

		std::list<std::string> _chunck;
	private:
		int			_socket, _timeout, _recvEnd, _time, _length, _size;
		std::string	_dir, _login, _msg;
		sockaddr_in	_address;
		bool		_work;
		unsigned long long _pos;
};

#endif // !REQUEST_HPP