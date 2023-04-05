#pragma once
#include "dbmanager.h"
/**
 * @brief Abstract Class for all the controller
*/
class AbstractController
{
public:
	/**
	 * @brief Virtual Destructor of the abstract class
	*/
	virtual ~AbstractController() {}
	/**
	 * @brief Virtual method that called the method associate to the class
	 * @param id the id that will be control 
	 * @param jeu name of the game which is played
	*/
	virtual void control(int id, QString jeu = "") = 0;
};
/**
 * @brief Controller which is use when a parcours is removed 
*/
class ControllerRemoveParcours : public AbstractController
{
private:
	DbManager* db;
public:
	/**
	 * @brief Contructor of the ControllerRemoveParcours class
	*/
	ControllerRemoveParcours();
	/**
	* @brief Destructor of the ControllerRemoveParcours class
	*/
	~ControllerRemoveParcours();
	/**
	 * @brief Method thats is called when a parcours is removed and called the remove method in the database class
	 * @param id the id of the parcours which is removed
	 * @param jeu unused here but for the ControllerAddScore class
	*/
	void control(int id ,QString jeu = "") override;
};
/**
 * @brief Controller which is called when a game end and a score is added to the database
*/
class ControllerAddScore : public AbstractController
{
private:
	DbManager* db;
public:
	/**
	* @brief Contructor of the ControllerAddScore class
	*/
	ControllerAddScore();
	/**
	 * @brief Destructor of the ControllerAddScore class
	*/
	~ControllerAddScore();
	/**
	 * @brief Method thats is called when a game ended and called the database method to add a score to the table
	 * @param id id of the player that play the game
	 * @param jeu name of the game played
	*/
	void control(int id, QString jeu = "") override;
};