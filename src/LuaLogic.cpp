
#include "LuaLogic.h"

LuaLogic::LuaLogic(Node *node, const char *path) : node(node) {
	state.open_libraries();
	state.load_file(path)();
	state.new_usertype<Node>("node",
	                         "move", (void(Node::*)(float, float, float))&Node::move,
	                         "multiplyScale", (void(Node::*)(float, float, float))&Node::multiplyScale,
	                         "getScale", &Node::getScale,
	                         "rotate", (void(Node::*)(float, float, float, float))&Node::rotate,
	                         "setScale", (void(Node::*)(float, float, float))&Node::setScale
	);

	state.new_usertype<glm::tvec3<float>>("tvec3",
	                                      "x", &glm::tvec3<float>::x,
	                                      "y", &glm::tvec3<float>::y,
	                                      "z", &glm::tvec3<float>::z
	);

	state["deadTime"] = 5.0f;
	state["growSpeed"] = 1.01f;
	state["maxScale"] = 4.0f;
}

void LuaLogic::operator()(Node &node, float dt, Scene &scene) {
	state["node"] = &node;

	state["tick"](dt);
}

