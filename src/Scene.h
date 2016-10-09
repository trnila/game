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

class Scene : public KeyListener, public MouseListener {
public:
	Scene(Window &window);

	void initResources();
	void update(float time);
	void renderOneFrame(RenderContext &context);

	virtual void onKey(int key, int scancode, int action, int mods) override;

	virtual void onMove(double x, double y) override;

private:
	NodeList root;
	NodeList *windMill;

	Program prog;
	Camera camera;
	CameraHandler camHandler;
	float deadTime;

	void createScene();
};
