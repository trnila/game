#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "Program.h"
#include "Object.h"
#include "ResourceManager.h"
#include "RenderContext.h"
#include "KeyListener.h"
#include "MouseListener.h"
#include "CameraHandler.h"
#include "Window.h"
#include "NodeList.h"
#include "FrameBuffer.h"
#include "Skybox.h"
#include "ObjectFactory.h"
#include "Logic.h"

class Scene : public KeyListener, public MouseListener {
public:
	Scene(Window &window);

	void update(float time);
	void renderOneFrame(RenderContext &context);

	virtual void onKey(int key, int scancode, int action, int mods) override;
	virtual void onMove(double x, double y) override;
	virtual void onClick(int button, int action, double x, double y) {
		if (action != GLFW_PRESS) {
			return;
		}

		int newY = window.getHeight() - y;
		float depth;

		//glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		int index;
		glReadPixels(x, newY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		printf("%f %f %d\n", x, y, index);
		Object* o = root.find(index);
		if (o && button == GLFW_MOUSE_BUTTON_1) {
			o->move(1, 1, 1);
		}
		else if(button == GLFW_MOUSE_BUTTON_2) {
			glm::vec3 screenX = glm::vec3(x, newY, depth);
			glm::mat4 view = camera.getTransform();
			glm::mat4 projection = camera.getPerspective();

			glm::vec4& viewPort = glm::vec4(0, 0, window.getWidth(), window.getHeight());
			glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

			printf("unProject[%f, %f, %f, %f]\n", pos.x, pos.y, pos.z, depth);



			/*Object *obj;
			obj = factory->create("resources/Headcrab classic/headcrabclassic.obj");
			obj->setColor(1, 1, 1);
			obj->setPosition(pos.x, pos.y, pos.z);
			obj->setScale(0.05f);
			obj->attachLogic<FollowLogic>(&camera);
			root.addNode(obj);*/

			Object *obj;
			obj = factory->create("resources/tree.obj");
			obj->setPosition(pos.x, pos.y, pos.z);
			obj->rotate(0, 0, 0, 1);
			obj->setScale(0.01);
			obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
			obj->attachLogic<TreeLogic>(1.01, 0.1, 5);
			root.addNode(obj);
		}

	}

private:
	NodeList root;
	NodeList *windMill, *propeller;
	Light *lights[8];

	Program prog, constantProg, shadow;
	Camera camera;
	CameraHandler camHandler;

	void createScene();
	void initResources();

	FrameBuffer *depthBuffer;
	Window &window;
	NodeList *lightContainer;
	Skybox *skybox;
	ObjectFactory* factory;
};
