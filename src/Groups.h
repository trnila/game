#pragma once

#include "Scene/Lights/PointLight.h"
#include "Scene/NodeList.h"
#include "Scene/GeneratedTerrain.h"
#include "Logic.h"
#include "Game.h"

struct Forest {
	void operator()(Scene* scene) {
		NodeList *forest = scene->getRootNode().createGroup();
		forest->move(17.65, -3.0, 26.88);

		Object *obj = forest->createEntity("resources/tree.obj");
		obj->setPosition(4, 0.0f, 0);
		obj->rotate(0, 0, 0, 1);
		obj->setScale(0.001, 0.001, 0.001);
		obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
		obj->attachLogic(TreeLogic(1.01, 0.1, 5));

		obj = forest->createEntity("resources/tree.obj");
		obj->setPosition(0, 0.0f, 0);
		obj->rotate(0, 0, 0, 1);
		obj->setScale(0.001, 0.001, 0.001);
		obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
		obj->attachLogic(TreeLogic(1.04, 0.2, 9));
	}
};

struct TwoCubes {
	void operator()(Scene* scene) {
		NodeList* cubes = scene->getRootNode().createGroup();
		cubes->move(10.7, 0.78, 8.81);

		Object *obj = cubes->createEntity("resources/cube.obj");
		obj->setPosition(0, 0, 0);
		obj->setColor(1, 0, 0);
		obj->attachLogic(RotateLogic(40));

		obj = cubes->createEntity("resources/cube.obj");
		obj->setPosition(-2, 0, 3);
		obj->setColor(1, 0, 0);
		obj->rotate(0, -1, 0, 0);
		obj->attachLogic(RotateLogic(40));
	}
};

struct Balls {
	void operator()(Scene* scene) {
		NodeList *balls = scene->getRootNode().createGroup();
		balls->move(15, 0, 0);

		float coords[][3] = {
				{0, 0, -1},
				{1, 0, 0},
				{0, 0, 1},
				{-1, 0, 0}
		};
		int modif = 2;
		for(int i = 0; i < 4; i++) {
			Object *obj = balls->createEntity("resources/ball.obj");
			obj->setPosition(modif * coords[i][0], modif * coords[i][1], modif * coords[i][2]);
		}

		BaseLight *light = balls->createLight<PointLight>(1);
		light->setDiffuseColor(Color(1, 0, 0));
		light->setSpecularColor(Color(1, 0, 0));
		light->setPosition(glm::vec3(0, 1, 0));
		balls->addNode(light);
	}
};

struct Earth {
	void operator()(Scene* scene) {
		NodeList *ro = scene->getRootNode().createGroup();
		ro->rotate(0, 0, 1, 0);
		ro->setPosition(600, 200, 600);
		ro->attachLogic(RotateLogic(20));

		NodeList *e1 = ro->createGroup();
		e1->rotate(0, 0, 1, 0);

		NodeList *e2 = e1->createGroup();
		e2->rotate(0, 0, 1, 0);
		e2->setPosition(100, 0, 0);

		Object *obj = e2->createEntity("resources/earth/earth.obj");
		obj->setColor(1, 1, 1);
		obj->setScale(0.05f);

		NodeList *m = e2->createGroup();
		m->rotate(0, 0, 1, 0);
		m->attachLogic(RotateLogic(-90));

		obj = m->createEntity("resources/moon/moon.obj");
		obj->setColor(1, 1, 1);
		obj->setPosition(20, 0, 0);
		obj->setScale(0.05f);
	}
};

struct RotatingSpotLight {
	void operator()(Scene* scene) {
		NodeList *node = scene->getRootNode().createGroup();
		node->setPosition(18.837509, 5.312332, 0.827486);

		NodeList *rot = node->createGroup();
		rot->attachLogic(RotateLogic(45));
		rot->rotate(0, 0, 1, 0);

		SpotLight *light = rot->createLight<SpotLight>(2);
		light->setDiffuseColor(Color(0, 1, 0));
		light->setSpecularColor(Color(0, 1, 0));
		light->setPosition(5, 0, 0);
		light->setDirection(glm::vec3(0, -1, 0));
	}
};

struct CombineScanner {
	void operator()(Scene* scene) {
		NodeList *center = scene->getRootNode().createGroup();
		center->setPosition(18, 0, 5);

		Object *obj = center->createEntity("resources/Combine Scanner/Combine_Scanner.obj");
		obj->setColor(1, 1, 1);
		obj->setScale(0.01f);

		SpotLight *light = center->createLight<SpotLight>(6);
		light->setDiffuseColor(Color(1, 1, 1));
		light->setSpecularColor(Color(1, 1, 1));
		light->setConeAngle(15);
		center->attachLogic(FollowLogic(&scene->getActiveCamera(), light));
	}
};

struct VariousObjects {
	void operator()(Scene* scene) {
		NodeList *root = scene->getRootNode().createGroup();
		root->setPosition(188.013016, 33.348019, 208.685776);
		scene->getActiveCamera().setPosition(188.013016, 33.348019, 208.685776);

		Object *obj = root->createEntity("resources/monkey.obj");
		obj->setPosition(13, 0, 3);
		obj->setColor(1, 0, 0);
		obj->rotate(0, 0, -1, 0);
		obj->attachLogic(RotateLogic(40));

		//obj = root->createEntity("resources/plane.obj");
		//obj->setScale(10);

		obj = root->createEntity("resources/monkey_smooth.obj");
		obj->setPosition(10, 0, 3);
		obj->setColor(1, 0, 0);
		obj->rotate(0, 0, 1, 0);
		obj->attachLogic(RotateLogic(40));

		obj = root->createEntity("resources/Vortigaunt/vortigaunt.obj");
		obj->setPosition(15, 0, 5);
		obj->setScale(0.02);
		obj->attachLogic(OnGround(glm::vec3(0)));

		obj = root->createEntity("resources/D0G/a.obj");
		obj->attachLogic(OnGround(glm::vec3(0)));
		obj->setPosition(16, 0, 5);

		obj = root->createEntity("resources/Strider/Strider.obj");
		obj->setColor(1, 1, 1);
		obj->setPosition(18, -5, 30);
		obj->setScale(0.02f);
		obj->attachLogic(OnGround(glm::vec3(0)));

		obj = scene->getRootNode().createEntity("resources/Combine Dropship/Combine_dropship.obj");
		obj->setColor(1, 1, 1);
		obj->setPosition(18, -5, 30);
		obj->setScale(0.02f);
		obj->attachLogic(Walker());
	}
};

void create_water(Scene* scene);

struct SkyboxFactory {
	SkyboxFactory(const char* path) : path(path) {}

	void operator()(Scene* scene) {
		Skybox *skybox = new Skybox(path, scene->getActiveCamera());
		scene->getRootNode().addNode(skybox);
	}

private:
	const char* path;
};

void normal_terrain(Scene* scene);

struct CameraFactory {
	CameraFactory(Game *game) : game(game) {}

	void operator()(Scene *scene);

private:
	Game *game;
};