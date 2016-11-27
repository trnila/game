#pragma once

#include "Scene/Lights/SpotLight.h"

class RotateLogic {
public:
	RotateLogic(float anglePerSec): anglePerSec(anglePerSec) {}

	void operator()(Node& node, float dt) {
		node.addAngle(anglePerSec * dt);
	}

private:
	float anglePerSec;
};

class TreeLogic {
public:
	TreeLogic(float growSpeed, float maxScale, float deadTime) : growSpeed(growSpeed), maxScale(maxScale), deadTime(deadTime) {}

	void operator()(Node& node, float dt) {
		if (node.getScale().x > maxScale) {
			node.rotate(90, 0, 0, 1);
			currentDeadTime += dt;

			if (currentDeadTime > deadTime) {
				node.rotate(0, 0, 0, 1);
				node.setScale(0.001, 0.001, 0.001);
				currentDeadTime = 0;
			}
		} else {
			node.multiplyScale(growSpeed, growSpeed, growSpeed);
		}
	}

private:
	float deadTime;
	float growSpeed;
	float maxScale;
	float currentDeadTime = 0;
};


struct MoveLogic {
	MoveLogic(glm::vec3 dir): dir(dir) {}

	void operator()(Node& node, float dt) {
		node.move(dir * dt);
	}

private:
	glm::vec3 dir;

};

class FollowLogic: public Observer<Camera> {
public:
	FollowLogic(Camera *cam, SpotLight *light): cam(cam), light(light) {
		id = rand();
	}

	~FollowLogic() {
		cam->removeListener(this);
	}

	FollowLogic(const FollowLogic& that) { //TODO: we shall not to copy these objects!
		light = that.light;
		cam = that.cam;
		cam->addListener(this);
	}

	void operator()(Node& node, float dt) {
		auto direction = pos - node.getPosition();
		node.move(direction * dt);

		auto objDir = normalize(glm::vec3(0, 0, 1));
		auto toCamDir = normalize(cam->getPosition() - node.getPosition());

		angle = glm::degrees(acos(glm::dot(objDir, toCamDir)));
		axis = glm::cross(objDir, toCamDir);
		node.rotate(angle, axis);
		light->setDirection(glm::vec3(0, -1, 0));
	}

	virtual void updated(Camera &node) override {
		float m = 1.0f;
		auto r = glm::vec3(m * rand() / RAND_MAX, m * rand() / RAND_MAX, 0.5 * rand() / RAND_MAX);
		float n = rand() % 1 ? 1 : -1;
		pos = (cam->getPosition() + cam->getDirection() * 2.0f + r * n);
	}

	float r() {
		return (float) rand() / RAND_MAX * 2 - 1;
	}

private:
	Camera *cam;
	glm::vec3 pos;

	float angle = 0;
	glm::vec3 axis;

	SpotLight* light;
	int id;
};