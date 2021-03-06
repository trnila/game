#pragma once

#include <unordered_map>
#include "Input/KeyListener.h"
#include "Scene/Object.h"
#include "Scene/NodeList.h"
#include "ObjectFactory.h"
#include "States.h"
#include "Scene.h"
#include "Scene/Lights/DirectionalLight.h"
#include "Game.h"

class State {
public:
	virtual void onClick(glm::vec3 pos, Object *object, Scene &root){}
	virtual void onKey(int key, int scancode, int action, int mods, Game *game) {
		if(action == GLFW_PRESS) {
			if(key == GLFW_KEY_ESCAPE) {
				game->getStates()->change(StateType::Normal);
			}

			auto it = transitionKeys.find(key);
			if(it != transitionKeys.end()) {
				game->getStates()->change(it->second);
			}
		}
	}

	void registerTransition(StateType state, int key) {
		transitionKeys[key] = state;
	}

private:
	std::unordered_map<int, StateType> transitionKeys;
};

class Insert: public State {
public:
	void onClick(glm::vec3 pos, Object *object, Scene &root) override {
		Object *obj;
		obj = object->getParent()->createEntity("resources/tree.obj");
		obj->setPosition(pos.x, pos.y, pos.z);
		obj->rotate(0, 0, 0, 1);
		obj->setScale(0.1);
		obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
		obj->attachLogic(TreeLogic(1.01, 0.1, 5));
		root.getRootNode().addNode(obj);
	}
};

class Delete: public State {
public:

	void onClick(glm::vec3 pos, Object *object, Scene &root) override {
		if(object) {
			object->getParent()->removeNode(object);
			delete object;
		}
	}
};

class Scale: public State {
public:

	virtual void onKey(int key, int scancode, int action, int mods, Game *game) override {
		if(action == GLFW_PRESS && key == GLFW_KEY_R) {
			larger = !larger;
		} else {
			State::onKey(key, scancode, action, mods, game);
		}
	}

	void onClick(glm::vec3 pos, Object *object, Scene &root) override {
		object->multiplyScale(glm::vec3(larger ? 1.5f : 0.5f));
	}

private:
	bool larger = 1;
};

class Lights: public State {
public:

	virtual void onKey(int key, int scancode, int action, int mods, Game *game) override {
		if(action == GLFW_PRESS) {
			BaseLight* l = game->getScene()->getRootNode().getLight(this->light);
			if(l) {
				switch(key) {
					case GLFW_KEY_T:
						l->setActive(!l->isActive());
						return;
					case GLFW_KEY_P:
						l->setPosition(game->getScene()->getActiveCamera().getPosition());
						printf("(%f, %f, %f)\n", l->getPosition().x, l->getPosition().y, l->getPosition().z);
						return;
					case GLFW_KEY_D: {
						DirectionalLight *light = dynamic_cast<DirectionalLight *>(l);
						if(light) {
							light->setDir(game->getScene()->getActiveCamera().getDirection());
							printf("(%f, %f, %f)\n", light->getDir().x, light->getDir().y, light->getDir().z);
						}
						return;
					}
					case GLFW_KEY_A:
						//l->setType(LightType::Directional);
						return;
					case GLFW_KEY_B:
						//l->setType(LightType::Point);
						return;
					case GLFW_KEY_C:
						//l->setType(LightType::SpotLight);
						//l->setConeAngle(30);
						return;
				}
			}

			if(key >= GLFW_KEY_0 && key <= GLFW_KEY_9) {
				light = key - GLFW_KEY_0;
				return;
			}
		}

		State::onKey(key, scancode, action, mods, game);
	}

private:
	int light = 1;
};

class Shoot : public State {
public:

	virtual void onKey(int key, int scancode, int action, int mods, Game *game) override {
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
			glm::vec3 pos = game->getScene()->getActiveCamera().getPosition();

			Object *obj;
			obj = game->getScene()->getRootNode().createEntity("resources/ball.obj");
			obj->setPosition(pos.x, pos.y, pos.z);
			obj->rotate(0, 0, 0, 1);
			obj->setScale(0.05);
			obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
			obj->attachLogic(MoveLogic(game->getScene()->getActiveCamera().getDirection()));
			obj->attachLogic(DestroyLogic(5));
			game->getScene()->getRootNode().addNode(obj);
		}
	}
};