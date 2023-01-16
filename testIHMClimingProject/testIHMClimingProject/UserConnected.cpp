#include "UserConnected.h"

UserConnected* UserConnected::usr = nullptr;

UserConnected::UserConnected(QString _name) : name(_name) {

}

UserConnected::~UserConnected()
{
	delete usr;
}

UserConnected* UserConnected::getInstance()
{
	if (usr == nullptr) {
		usr = new UserConnected("");
	}
	return usr;
}

void UserConnected::disconnect()
{
	usr = nullptr;
	name = "";
}

QString UserConnected::getName()
{
	return name;
}

void UserConnected::setName(QString set)
{
	name = set;
}
