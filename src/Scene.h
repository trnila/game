#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "Graphics/Program.h"
#include "Scene/Object.h"
#include "Utils/ResourceManager.h"
#include "Graphics/RenderContext.h"
#include "Input/KeyListener.h"
#include "Input/MouseListener.h"
#include "Scene/CameraHandler.h"
#include "Window.h"
#include "Scene/NodeList.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/Skybox.h"
#include "ObjectFactory.h"
#include "Logic.h"
#include "Graphics/State.h"

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

		Object* o = root.find(index);

		glm::vec3 screenX = glm::vec3(x, newY, depth);
		glm::mat4 view = camera.getTransform();
		glm::mat4 projection = camera.getPerspective();

		glm::vec4 viewPort = glm::vec4(0, 0, window.getWidth(), window.getHeight());
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		states.current().onClick(pos, o, root);
	}

private:
	NodeList root;
	NodeList *windMill, *propeller;

	Program prog, constantProg, shadow;
	Camera camera;
	CameraHandler camHandler;

	void createScene();
	void initResources();

	FrameBuffer *depthBuffer;
	Window &window;
	Skybox *skybox;
	ObjectFactory* factory;
	States states;
};
