#include <glm/ext.hpp>
#include <random>
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

	float terrainHeight = scene.getTerrain()->getHeightAt(node.getPosition().x, node.getPosition().z);
	if(terrainHeight > node.getPosition().y) {
		pos.y = terrainHeight + 3;
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
		glm::vec3 dir = glm::vec3(rand_float(-1, 1), 0, rand_float(-1, 1));
		obj->setDirection(dir);
		obj->setPosition(node.getPosition());
		//obj->attachLogic(TerrainMove(dir));
		obj->attachLogic(MoveLogic(glm::vec3(0, -1, 0)));
		obj->attachLogic([=](Node &node, float dt, Scene &scene) -> void {
			float height = scene.getTerrain()->getHeightAt(node.getPosition().x, node.getPosition().z);
			if(node.getPosition().y <= height) {
				node.removeAllLogic();
				node.attachLogic(TerrainMove(normalize(dir))); //TODO: use object.getDirection
			}
		});
	}
}

void TerrainMove::operator()(Node &node, float dt, Scene &scene) {
	node.move(dir * dt);

	float terrainHeight = scene.getTerrain()->getHeightAt(node.getPosition().x, node.getPosition().z);
	node.setPosition(node.getPosition().x, terrainHeight, node.getPosition().z);
}

void CamInit::operator()(Node &node, float diff, Scene &scene) {
	time += diff;

	float height = scene.getTerrain()->getHeightAt(node.getPosition().x, node.getPosition().z);
	if(node.getPosition().y + 2 <= height) {
		node.attachLogic(OnGround(glm::vec3(0, 1, 0)));
	} else {
		node.move(0, -(time * time / 2.0f), 0);
	}
}

void OnGround::operator()(Node &node, float diff, Scene &scene) {
	glm::vec3 pos = node.getPosition();
	pos.y = scene.getTerrain()->getHeightAt(node.getWorldPosition().x, node.getWorldPosition().z);
	pos.y -= node.getParent()->getPosition().y;

	pos += offset;

	node.setPosition(pos);
}

void Bezier::operator()(Node &node, float dt, Scene &scene) {
	time += dt;
	float t = time / duration;
	if(t > 1.0f) {
		success(node);
		return;
	}


	glm::vec3 result{0};
	for(int i = 0; i < points.size(); i++) {
		float B = bernstein(i, points.size(), t);
		result.x += points[i].x * B;
		result.y += points[i].y * B;
		result.z += points[i].z * B;
	}

	result.y = std::max(result.y, scene.getTerrain()->getHeightAt(result.x, result.z) + 1);

	//printf("%f [%f, %f, %f]\n", t, result.x, result.y, result.z);
	node.setPosition(result);
}

void DestroyLogic::operator()(Node &node, float dt, Scene &scene) {
	curTime += dt;

	if(time < curTime) {
		node.getParent()->removeNode(&node);
	}
}
