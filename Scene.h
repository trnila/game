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

class Scene : public KeyListener, public MouseListener {
public:
	Scene(Window &window);
	int init_resources();
	void update(float time);
	void renderOneFrame(RenderContext &context);

	virtual void onKey(int key, int scancode, int action, int mods) override;
	virtual void onMove(GLFWwindow *window, double x, double y) override;

private:
	Program prog;
	Camera camera;
	CameraHandler camHandler;

	std::vector<Object> objects;

	float deadTime;

};
