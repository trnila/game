#pragma once

#include <assimp/LogStream.hpp>
#include <ostream>

class StreamLog: public Assimp::LogStream {
public:
	StreamLog(std::ostream &out): out(out) {}

	void write(const char* message);

private:
	std::ostream &out;
};

