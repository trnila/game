#pragma once

#include <vector>
#include <algorithm>

template<typename T>
class Observer {
public:
	virtual void updated(T &obj) = 0;
};


template<typename T>
class Subject {
public:
	void addListener(Observer<T> *observer) {
		listeners.push_back(observer);
	}

	void removeListener(Observer<T> *observer) {
		listeners.erase(std::remove(listeners.begin(), listeners.end(), observer), listeners.end());
	}

protected:
	void notify() {
		for (Observer<T> *observer: listeners) {
			observer->updated(static_cast<T &>(*this));
		}
	}

private:
	std::vector<Observer<T> *> listeners;
};