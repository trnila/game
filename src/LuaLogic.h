#pragma once

#include "sol.hpp"

class Node;
class Scene;

class LuaLogic {
public:
	LuaLogic(Node *node, const char *path);

	void operator()(Node& node, float dt, Scene& scene);

	sol::state &getState() {
		return state;
	}

private:
	Node *node;
	sol::state state;
};


class LuaLogicHolder {
public:
	LuaLogicHolder(LuaLogic *ptr): ptr(ptr) {}
	void operator()(Node& node, float dt, Scene& scene) {
		ptr->operator()(node, dt, scene);
	}

private:
	LuaLogic* ptr;
};