#pragma once


class Observer {
public:
	virtual ~Observer() {}
	virtual void updateModel() = 0;
};

class Observable {
public:
	virtual ~Observable() {}
	virtual void addObserver(Observer* observer) = 0;
	virtual void removeObserver(Observer* observer) = 0;
	virtual void notifyObserver() const = 0;
};
