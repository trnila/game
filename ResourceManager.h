#pragma once

#include <unordered_map>

template<typename T>
class ResourceManager {
public:
	static ResourceManager<T>& getInstance() {
		return instance;
	}

	template<typename... Args>
	T& getResource(const char *filename, Args... arg) {
		auto it = resources.find(std::string(filename));
		if(it != resources.end()) {
			return it->second;
		}

		resources[filename] = T(filename, arg...);
		return resources.find(filename)->second;
	}

private:
	ResourceManager() {}
	std::unordered_map<std::string, T> resources;

	static ResourceManager<T> instance;
};

template<typename T>
ResourceManager<T> ResourceManager<T>::instance;
