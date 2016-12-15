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
#include "Panel.h"


class Scene {
public:
	Scene(Camera *camera);

	void update(float time);
	void renderOneFrame(RenderContext &context);
	

	NodeList &getRootNode() {
		return *root;
	}

	Camera& getActiveCamera() {
		return camera;
	}

	States& getStates() {
		return states;
	}

	Terrain *getTerrain() const;

	void onClick(glm::vec3 tvec3, Object *obj);

private:
	NodeList *root;

	Program prog;
	Camera &camera;

	void createScene();
	void initResources();

	Skybox *skybox;
	States states;
	ShadowRenderer shadowRenderer;
	Terrain *terrain;

	void createTerrain();
	void createObjects();
	void createSkybox();
};
