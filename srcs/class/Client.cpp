#include "../../includes/class/Client.hpp"

Client::Client()
{

}

Client::Client(const Client &other)
{
	setSocket(other.getSocket());
	setTimeout(other.getTimeout());
	setDir(other.getDir());
	setRecvEnd(other.getRecvEnd());
	setAddress(other.getAddress());
	setTime(other.getTime());
}

Client::~Client()
{

}

Client &Client::operator=(const Client &other)
{
    if (this == &other) return(*this);
    this->~Client();
    return *new(this) Client(other);
}

Client::Client(int socket)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	setSocket(socket);
	setTimeout(0);
	setTime(time.tv_sec);
	setRecvEnd(0);
}

void Client::setSocket(int value)
{
	this->_socket = value;
}

void Client::setTimeout(int value)
{
	this->_timeout = value;
}

void Client::setTime(int value)
{
	this->_time = value;
}

void	Client::setDir(std::string value)
{
	this->_dir = value;
}

void Client::setRecvEnd(int value)
{
	this->_recvEnd = value;
}

void Client::setAddress(sockaddr_in value)
{
	this->_address = value;
}

int Client::getSocket() const
{
	return(this->_socket);
}

int Client::getTimeout() const
{
	return(this->_timeout);
}

int Client::getTime() const
{
	return(this->_time);
}

std::string Client::getDir() const
{
	return(this->_dir);
}

int Client::getRecvEnd() const
{
	return(this->_recvEnd);
}

sockaddr_in Client::getAddress() const
{
	return(this->_address);
}

std::string Client::getLogin() const
{
	return(this->_login);
}

// int b64_isvalidchar(char c)
// {
// 	if (c >= '0' && c <= '9')
// 		return 1;
// 	if (c >= 'A' && c <= 'Z')
// 		return 1;
// 	if (c >= 'a' && c <= 'z')
// 		return 1;
// 	if (c == '+' || c == '/' || c == '=')
// 		return 1;
// 	return 0;
// }

// size_t b64_decoded_size(std::string in)
// {
// 	size_t len;
// 	size_t ret;
// 	size_t i;

// 	len = in.length();
// 	ret = len / 4 * 3;

// 	for (i=len; i-->0; ) {
// 		if (in[i] == '=') {
// 			ret--;
// 		} else {
// 			break;
// 		}
// 	}

// 	return ret;
// }

// int b64_decode(std::string in, unsigned char *out, size_t outlen)
// {
// 	size_t len;
// 	size_t i;
// 	size_t j;
// 	int    v;
// 	int b64invs[] = { 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
// 	59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
// 	6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
// 	21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
// 	29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
// 	43, 44, 45, 46, 47, 48, 49, 50, 51 };

// 	len = in.length();
// 	if (outlen < b64_decoded_size(in) || len % 4 != 0)
// 		return 0;

// 	for (i=0; i<len; i++) {
// 		if (!b64_isvalidchar(in[i])) {
// 			return 0;
// 		}
// 	}

// 	for (i=0, j=0; i<len; i+=4, j+=3) {
// 		v = b64invs[in[i]-43];
// 		v = (v << 6) | b64invs[in[i+1]-43];
// 		v = in[i+2]=='=' ? v << 6 : (v << 6) | b64invs[in[i+2]-43];
// 		v = in[i+3]=='=' ? v << 6 : (v << 6) | b64invs[in[i+3]-43];

// 		out[j] = (v >> 16) & 0xFF;
// 		if (in[i+2] != '=')
// 			out[j+1] = (v >> 8) & 0xFF;
// 		if (in[i+3] != '=')
// 			out[j+2] = v & 0xFF;
// 	}

// 	return 1;
// }

// std::string parse_authorization(Request *_req)
// {
// 	std::string auth = _req->getAuthorization();
// 	std::string cred;

// 	if (auth.empty())
// 		return ("");
// 	auth.erase(std::remove_if(auth.begin(), auth.end(), isspace), auth.end());
// 	if (!ft_strncmp(auth.c_str(), "Authorization:Basic", 19))
// 		return (auth.substr(19, auth.length()));
// 	return ("");
// }

// void Client::setLogin()
// {
// 	std::string			ret;
// 	char				*out;
// 	size_t				out_len;
// 	std::string			enc = parse_authorization(_req);

// 	if (enc.empty()){
// 		_login = "NotAuth";
// 		return ;
// 	}
// 	out_len = b64_decoded_size(enc)+1;
// 	out = (char *)malloc(out_len);

// 	if (!b64_decode(enc, (unsigned char *)out, out_len)) {
// 		_login = "Error";
// 		return ;
// 	}
// 	out[out_len - 1] = '\0';
// 	ret = out;
// 	free(out);
// 	_login = ret;
// }
