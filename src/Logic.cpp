#include <glm/ext.hpp>
#include <iostream>
#include "Logic.h"

void RotateLogic::update(float diff) {
	obj.addAngle(anglePerSec * diff);
}

void TreeLogic::update(float diff) {
	if (obj.getScale().x > maxScale) {
		obj.rotate(90, 0, 0, 1);
		currentDeadTime += diff;

		if (currentDeadTime > deadTime) {
			obj.rotate(0, 0, 0, 1);
			obj.setScale(0.001, 0.001, 0.001);
			currentDeadTime = 0;
		}
	} else {
		obj.multiplyScale(growSpeed, growSpeed, growSpeed);
	}
}

MoveLogic::MoveLogic(Node &obj) : Logic(obj) {}

void MoveLogic::update(float diff) {
	obj.move(0, 1.0 * diff, 0);
}

FollowLogic::FollowLogic(Node &obj, Camera *cam) : Logic(obj), cam(cam) {

}

void FollowLogic::update(float diff) {
	glm::vec3 pos = (cam->getPosition() + cam->getDirection() * 2);
	obj.setPosition(pos);

	auto objDir = normalize(glm::vec3(0, 0, 1));
	auto toCamDir = normalize(cam->getPosition() - obj.getPosition());

	float angle = acos(glm::dot(objDir, toCamDir));
	auto axis = glm::cross(objDir, toCamDir);
	obj.rotate(glm::degrees(angle), axis);

}
