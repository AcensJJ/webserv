#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <unistd.h>
#include "../../libft-cpp/include/libft.hpp"
#include "../../libft-cpp/include/get_next_line.hpp"

#include "Request.hpp"
#include "Response.hpp"

class Client {
    public:
		Client();
		Client(const Client &other);
		Client &operator=(const Client &other);
		~Client();

		void	setRequest(Request *value);
		void	setResponse(Response *value);
		void	setSocket(int value);
		Request	*getRequest() const;
		Response	*getResponse() const;
		int	getSocket() const;

	private:
		Request *_req;
		Response *_res;
		int _socket;
};

#endif // !REQUEST_HPP