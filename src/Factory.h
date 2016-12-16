#pragma once

#include <functional>
#include <vector>

class Scene;

class Factory {
public:
	typedef std::function<void(Scene*)> FactoryFn;

	void add(std::vector<FactoryFn> collection) {
		groups.insert(groups.end(), collection.begin(), collection.end());
	}

	void fillScene(Scene& scene);

private:
	std::vector<FactoryFn> groups;
};


