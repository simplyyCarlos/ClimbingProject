#pragma once
#include "qstring.h"
/**
 * @brief Singleton class that conatins the information of the connected user
*/
class UserConnected
{
private:

	static UserConnected* usr;
	QString name;
	/**
	 * @brief Private constructor called in the getInstance Method
	 * @param _name pseudo of the connected user 
	*/
	UserConnected(QString _name);
public:
	/**
	 * @brief Destructor of the class
	*/
	~UserConnected();
	/**
	 * @brief Set up of the singleton, delete the destructor by copy
	 * @param uc
	*/
	UserConnected(UserConnected& uc) = delete;
	/**
	 * @brief Set up of the singleton, delete the override '=' method
	 * @param
	*/
	void operator=(const UserConnected&) = delete;
	/**
	 * @brief Singleton method to initialize and get the instance
	 * @return the instance of the class
	*/
	UserConnected* getInstance();
	/**
	 * @brief set the name at null to deconnect the player 
	*/
	void disconnect();
	/**
	 * @brief method to get the pseudo of the player 
	 * @return pseudo of the player 
	*/
	QString getName();
	/**
	 * @brief change the name of the user connected 
	 * @param set pseudo to set
	*/
	void setName(QString set);
};

