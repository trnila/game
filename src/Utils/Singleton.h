#pragma once

template<typename T>
class Singleton {
public:
	static T &getInstance() {
		return instance;
	}

private:
	// Singleton() {} //TODO: fix private constructor
	static T instance;
};

template<typename T>
T Singleton<T>::instance;
