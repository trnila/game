#pragma once

#include "Graphics/Program.h"
#include "Graphics/RenderContext.h"
#include "Graphics/FrameBuffer.h"
#include "Utils/ResourceManager.h"

class ShadowResult {
public:
	Texture *texture;
	glm::mat4 depthMVP;

	void apply(Program &program);
};

class ShadowRenderer {
public:
	ShadowRenderer() {
		program.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/shadow.v.glsl", GL_VERTEX_SHADER));
		program.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/shadow.f.glsl", GL_FRAGMENT_SHADER));
		program.link();

		program.use();
		depthBuffer = new FrameBuffer(1024, 1024, GL_DEPTH_COMPONENT);
	}

	~ShadowRenderer() {
		delete depthBuffer;
	}

	ShadowResult render(RenderContext &ctx, Scene *root);

	Program program;
private:
	FrameBuffer *depthBuffer;
};


