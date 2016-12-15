#pragma once
#include <glm/vec4.hpp>
#include "Scene.h"
#include "Utils/Singleton.h"
#include "Input/KeyListener.h"
#include "Input/MouseListener.h"
#include "Window.h"

class Game : public Singleton<Game>, public KeyListener, public MouseListener {
public:
	void init();

	void startRendering();

	virtual void onKey(int key, int scancode, int action, int mods) override;
	virtual void onMove(double x, double y) override;
	virtual void onClick(int button, int action, double x, double y) {
		if (action != GLFW_PRESS) {
			return;
		}

		int newY = window->getHeight() - y;
		float depth;

		glReadPixels(x, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		int index;
		glReadPixels(x, newY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		glm::vec3 screenX = glm::vec3(x, newY, depth);
		glm::mat4 view = scene->getActiveCamera().getLookAt();
		glm::mat4 projection = scene->getActiveCamera().getPerspective();

		glm::vec4 viewPort = glm::vec4(0, 0, window->getWidth(), window->getHeight());
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		scene->onClick(pos, scene->getRootNode().find(index));
	}

	
protected:
	Game() {};
	friend Singleton<Game>;

private:
	Window *window;
	Scene *scene;
};
