#pragma once

#include <stdexcept>

template<typename T, typename H>
class BindableResource {
public:
	H activate() {
		return H(static_cast<T&>(*this));
	}
};

template<typename T>
class LockImpl {
public:
	LockImpl(T& t): obj(t) {
		if(active) {
			//throw std::runtime_error("Another object is already activated!");
		}

		active = true;

		t.open();
	}

	~LockImpl() {
		obj.close();
		active = false;
	}

	T &obj;

private:
	static bool active;
};

template<typename T>
bool LockImpl<T>::active = false;
