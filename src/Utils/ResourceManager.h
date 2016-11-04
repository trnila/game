#pragma once

#include <unordered_map>
#include "Singleton.h"

template<typename T>
class ResourceManager : public Singleton<ResourceManager<T>> {
public:
	template<typename... Args>
	T& getResource(const char *filename, Args... arg) {
		auto it = resources.find(std::string(filename));
		if(it != resources.end()) {
			return *it->second;
		}

		resources.emplace(filename, new T(filename, arg...));
		return *resources.find(filename)->second;
	}

protected:
	friend class Singleton<ResourceManager<T>>;

private:
	ResourceManager() {}
	std::unordered_map<std::string, T*> resources;
};