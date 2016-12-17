#pragma once

#include "Scene/Node.h"
#include "sol.hpp"

class LuaLogic {
public:
	LuaLogic(Node *node, const char *path);

	void operator()(Node& node, float dt, Scene& scene);

private:
	Node *node;
	sol::state state;
};


