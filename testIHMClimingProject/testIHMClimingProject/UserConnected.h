#pragma once
#include "qstring.h"
class UserConnected
{
private:
	static UserConnected* usr;
	QString name;
	UserConnected(QString _name);
public:
	~UserConnected();
	UserConnected* getInstance();
	void disconnect();
	QString getName();
	void setName(QString set);
};

