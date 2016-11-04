#pragma once

#include <unordered_map>
#include "../Input/KeyListener.h"
#include "../Scene/Object.h"
#include "../Scene/NodeList.h"
#include "../ObjectFactory.h"

enum class StateType {
	Normal,
	Insert,
	Delete,
	Scale,
	Lights
};

class State;

class States {
public:
	void add(StateType type, State* state) {
		states[type] = state;
	}

	void change(StateType type) {
		actual = states[type];
	}

	State& current() {
		return *actual;
	}

private:
	std::unordered_map<StateType, State*> states;
	State* actual = nullptr;
};

class State {
public:
	State(States& states): states(states) {}

	virtual void onClick(glm::vec3 pos, Object *object, NodeList &root){}
	virtual void onKey(int key, int scancode, int action, int mods, NodeList &root) {
		std::unordered_map<int, StateType> m {
			  {GLFW_KEY_ESCAPE, StateType::Normal},
			  {GLFW_KEY_I, StateType::Insert},
			  {GLFW_KEY_X, StateType::Delete},
			  {GLFW_KEY_S, StateType::Scale},
			  {GLFW_KEY_L, StateType::Lights}
		};

		if(action == GLFW_PRESS) {
			auto it = m.find(key);
			if(it != m.end()) {
				states.change(it->second);
			}
		}
	}

private:
	States& states;
};

class NoState: public State {
public:
	NoState(States &states) : State(states) {}

};

class Insert: public State {
public:
	Insert(States &states, ObjectFactory &factory) : State(states), factory(factory) {}

	virtual void onKey(int key, int scancode, int action, int mods, NodeList &root) override {
		State::onKey(key, scancode, action, mods, root);
	}

	void onClick(glm::vec3 pos, Object *object, NodeList &root) override {
		Object *obj;
		obj = factory.create("resources/tree.obj");
		obj->setPosition(pos.x, pos.y, pos.z);
		obj->rotate(0, 0, 0, 1);
		obj->setScale(0.01);
		obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
		//obj->attachLogic<TreeLogic>(1.01, 0.1, 5);
		root.addNode(obj);
	}

private:
	ObjectFactory &factory;
};

class Delete: public State {
public:
	Delete(States &states) : State(states) {}

	void onClick(glm::vec3 pos, Object *object, NodeList &root) override {
		object->move(1000, 1000, 1000); // TODO: fix
	}
};

class Scale: public State {
public:
	Scale(States &states) : State(states) {}

	virtual void onKey(int key, int scancode, int action, int mods, NodeList &root) override {
		if(action == GLFW_PRESS && key == GLFW_KEY_R) {
			larger = !larger;
		} else {
			State::onKey(key, scancode, action, mods, root);
		}
	}

	void onClick(glm::vec3 pos, Object *object, NodeList &root) override {
		object->multiplyScale(glm::vec3(larger ? 1.5f : 0.5f));
	}

private:
	bool larger = 1;
};

class Lights: public State {
public:
	Lights(States &states, Camera &cam) : State(states), cam(cam) {}

	virtual void onKey(int key, int scancode, int action, int mods, NodeList &root) override {
		if(action == GLFW_PRESS) {
			Light* l = root.getLight(this->light);
			if(l) {
				switch(key) {
					case GLFW_KEY_T:
						l->setActive(!l->isActive());
						return;
					case GLFW_KEY_P:
						l->setPosition(cam.getPosition());
						return;
					case GLFW_KEY_D:
						l->setDirection(cam.getDirection());
						return;
					case GLFW_KEY_A:
						l->setType(LightType::Directional);
						return;
					case GLFW_KEY_B:
						l->setType(LightType::Point);
						return;
					case GLFW_KEY_C:
						l->setType(LightType::SpotLight);
						return;
				}
			}

			if(key >= GLFW_KEY_0 && key <= GLFW_KEY_9) {
				light = key - GLFW_KEY_0;
				return;
			}
		}

		State::onKey(key, scancode, action, mods, root);
	}

private:
	int light = 1;
	Camera &cam;
};
