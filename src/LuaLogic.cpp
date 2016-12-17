
#include "LuaLogic.h"

LuaLogic::LuaLogic(Node *node, const char *path) : node(node) {
	state.open_libraries();
	state.load_file(path)();
	state.new_usertype<Node>("node",
	                         "move", (void(Node::*)(float, float, float))&Node::move,
	                         "setPosition", (void(Node::*)(float, float, float))&Node::setPosition,
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

	auto data = {
			glm::vec3{142.136200, 35.926910, 178.578262},
			glm::vec3{200.470261, 32.839893, 223.659439},
			glm::vec3{91.863808, 41.696106, 269.774445},
	};
	state["points"] = data;
}

void LuaLogic::operator()(Node &node, float dt, Scene &scene) {
	state["node"] = &node;

	state["tick"](dt);
}

