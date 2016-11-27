#include <glm/ext.hpp>
#include "Logic.h"
#include "Scene/Lights/BaseLight.h"
#include "Scene.h"

void Walker::operator()(Node &node, float dt, Scene &scene) {
	Camera &cam = scene.getActiveCamera();

	time += dt;
	time2 += dt;
	time3 += dt;

	auto toCamDir = normalize(cam.getPosition() - pos);
	if(time2 > 1) {
		pos = (cam.getPosition() + cam.getDirection() * glm::vec3(1, 0.1, 1) * 20.0f);
		time2 = 0;
	}

	auto direction = pos - node.getPosition();
	node.move(direction * dt);

	auto objDir = normalize(glm::vec3(0, 0, 1));

	float angle = glm::degrees(acos(glm::dot(objDir, toCamDir)));
	glm::vec3 axis = glm::cross(objDir, toCamDir);
	node.rotate(angle, axis);

	if(time > 3) {
		Object *bullet = scene.getRootNode().createEntity("resources/ball.obj");
		bullet->setScale(0.5);
		bullet->setColor(rand() % 255 / 255.0, rand() % 255 / 255.0, rand() % 255 / 255.0);
		bullet->setPosition(node.getPosition() + glm::vec3(1.5, 1.5, 0));
		bullet->attachLogic(MoveLogic(toCamDir * 5.0f));
		bullet->attachLogic(DestroyLogic(5));
		time = 0;
	}

	if(time3 > 5) {
		time3 = 0;

		Object* obj = scene.getRootNode().createEntity("resources/Headcrab classic/headcrabclassic.obj");
		obj->setColor(1, 1, 1);
		obj->setPosition(node.getPosition());
		obj->attachLogic(MoveLogic(glm::vec3(0, -1, 0)));
		obj->attachLogic([](Node &node, float dt, Scene &scene) -> void {
			//float height = scene.getTerrain()->getHeightAt(node.getPosition().x, node.getPosition().z) - 3;
			float height = -1;
			if(node.getPosition().y <= height) {
				node.removeAllLogic();
				node.attachLogic(MoveLogic(glm::vec3(0.1, 0, 0)));
			}
		});
	}
}
