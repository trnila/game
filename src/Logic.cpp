#include <glm/ext.hpp>
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
	cam->addListener(this);
}

float r() {
	return (float) rand() / RAND_MAX * 2 - 1;
}

void FollowLogic::update(float diff) {
	time += diff;

	if(wandering) {
		if(time > 3) {
			if(rand() % 2) {
				pos = obj.getPosition() + glm::vec3(r(), r(), r());
			} else {
				axis = glm::vec3(0, r(), 0);
				angle = rand() % 180;
			}
			time = 0;

			if(rand() % 5 == 1) {
				wandering  = 0;
			}
		}

		auto direction = pos - obj.getPosition();
		obj.move(direction * diff);
		obj.rotate(obj.getAngle() + (angle - obj.getAngle()) * diff, axis);
	} else {
		if(time > 3) {
			wandering = true;
		} else {
			auto direction = pos - obj.getPosition();
			obj.move(direction * diff);

			auto objDir = normalize(glm::vec3(0, 0, 1));
			auto toCamDir = normalize(cam->getPosition() - obj.getPosition());

			angle = glm::degrees(acos(glm::dot(objDir, toCamDir)));
			axis = glm::cross(objDir, toCamDir);
			obj.rotate(angle, axis);
		}
	}
}

void FollowLogic::updated(Camera &obj) {
	if(!wandering) {
		float m = 1.0f;
		auto r = glm::vec3(m * rand() / RAND_MAX, m * rand() / RAND_MAX, 0.5 * rand() / RAND_MAX);
		int n = rand() % 1 ? 1 : -1;
		pos = (cam->getPosition() + cam->getDirection() * 2 + r * n);

		time = 0;
	}

}
