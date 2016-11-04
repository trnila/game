
#pragma once

#include <fstream>
#include <sstream>

class Formatter {
public:
	template<typename T>
	Formatter& operator<<(const T &item) {
		os << item;
		return *this;
	}

	operator std::string() const {
		return os.str();
	}

private:
	std::ostringstream os;
};