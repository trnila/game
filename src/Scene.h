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
#include "States.h"
#include "Terrain.h"
#include "Panel.h"
#include "ShadowRenderer.h"
#include "Factory.h"

class Scene {
public:
	Scene(Factory *camera);

	void update(float time);
	void renderOneFrame(RenderContext &context);
	

	NodeList &getRootNode() {
		return *root;
	}

	Camera& getActiveCamera() {
		return *camera;
	}

	Terrain *getTerrain() const;

	void registerProgram(Program *program) {
		programs.push_back(program);
	}

	void lightChanged(BaseLight *light) {
		for(Program* program: programs) {
			program->updated(*light);
		}
	}

	void setAmbientLight(Color color) {
		for(Program* program: programs) {
			program->setAmbientColor(color);
		}
	}

	ObjectFactory* getObjectFactory() {
		return factory;
	}

	void setActiveCamera(Camera* cam) {
		this->camera = cam;
	}

	ObjectFactory* factory;
private:
	NodeList *root;

	Program prog;
	Camera *camera;

	void initResources();

	ShadowRenderer shadowRenderer;
	Terrain *terrain;
	std::vector<Program*> programs;
};
