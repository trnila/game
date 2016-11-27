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
#include "ShadowRenderer.h"
#include "States.h"
#include "Terrain.h"


class Scene : public KeyListener, public MouseListener {
public:
	Scene(Window &window);

	void update(float time);
	void renderOneFrame(RenderContext &context);

	virtual void onKey(int key, int scancode, int action, int mods) override;
	virtual void onMove(double x, double y) override;
	virtual void onClick(int button, int action, double x, double y);

	NodeList &getRootNode() {
		return root;
	}

	Camera& getActiveCamera() {
		return camera;
	}

	ObjectFactory& getObjectFactory() {
		return *factory;
	}

	States& getStates() {
		return states;
	}

private:
	NodeList root;

	Program prog;
	Camera camera;
	CameraHandler camHandler;

	void createScene();
	void initResources();

	Window &window;
	Skybox *skybox;
	ObjectFactory* factory;
	States states;
	ShadowRenderer shadowRenderer;
	Terrain *terrain;

	Color ambientColor = Color(0.1, 0.1, 0.1);

	void createBalls();
	void createRotatingSpotLight();

	void createScanner();
};
