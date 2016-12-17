
#include "LuaLogic.h"

LuaLogic::LuaLogic(Node *node, const char *path) : node(node) {
	state.open_libraries();
	state.load_file(path)();
	state.new_usertype<Node>("node", "move", (void(Node::*)(float, float, float))&Node::move);
}

void LuaLogic::operator()(Node &node, float dt, Scene &scene) {
	state["node"] = &node;

	state["tick"](dt);
}
