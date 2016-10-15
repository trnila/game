#pragma once
#include <string>
#include <fstream>

std::string getFileContents(const char* path) {
	std::ifstream file(path);

	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return content;
}