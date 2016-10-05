#pragma once

#include <vector>
#include <algorithm>

class Camera;

class Observer {
public:
	virtual void notify(Camera &camera) = 0;
};


class Subject {
public:
	void addListener(Observer *observer) {
		listeners.push_back(observer);
	}

	void removeListener(Observer *observer) {
		listeners.erase(std::remove(listeners.begin(), listeners.end(), observer), listeners.end());
	}

protected:
	void notify();

private:
	std::vector<Observer*> listeners;
};