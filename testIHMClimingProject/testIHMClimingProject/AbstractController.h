#pragma once

class AbstractController
{
public:
	virtual ~AbstractController(){}
	virtual void control() = 0;
};