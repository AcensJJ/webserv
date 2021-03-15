#include "../../includes/class/Routes.hpp"

// COPLIEN
Routes::Routes()
{
	
}

Routes::Routes(const Routes &other)  : _http_method(other._http_method), _dir_file(other._dir_file),
 _listen(other._listen),  _default(other._default)
{

}

Routes::~Routes()
{

}

Routes &Routes::operator=(const Routes &other)
{
    if (this == &other) return(*this);
    this->~Routes();
    return *new(this) Routes(other);
}

// SET
void Routes::setDirFile(std::string value)
{
	this->_dir_file = value;
};

void Routes::setListen(bool value)
{
	this->_listen = value;
};

void Routes::setDefault(std::string value)
{
	this->_default = value;
};

void Routes::setLocation(std::string value)
{
	this->_location = value;
};

void Routes::setGCIPath(std::string value)
{
	this->_gci_path = value;
};

void Routes::setGCIExtension(std::string value)
{
	this->_gci_extension = value;
};


// GET
std::string Routes::getDirFile() const
{
	return (this->_dir_file);
};

bool Routes::getListen() const
{
	return (this->_listen);
};

std::string Routes::getDefault() const
{
	return (this->_default);
};

std::string Routes::getLocation() const
{
	return (this->_location);
};

std::string Routes::getGCIPath() const
{
	return (this->_gci_path);
};

std::string Routes::getGCIExtension() const
{
	return (this->_gci_extension);
};

