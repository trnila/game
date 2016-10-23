#pragma once
#include "Program.h"
#include "VBO.h"
#include "VAO.h"
#include "Camera.h"

enum class RenderStage {
	Shadow,
	Normal
};

class RenderContext {
public:
	void use(Program& program) {
		program.use();
	}

	void clearColor(float r, float g, float b, float a) {
		GL_CHECK(glClearColor(r, g, b, a));
	}

	void clear(int flags) {
		GL_CHECK(glClear(flags));
	}

	void drawArrays(int type, int start, int stop) {
		GL_CHECK(glDrawArrays(type, start, stop));
	}

	void setCamera(Camera *camera) {
		this->camera = camera;
	}

	Camera* getCamera() {
		return camera;
	}

	RenderStage getStage() const {
		return stage;
	}

	void setStage(RenderStage stage) {
		this->stage = stage;
	}

private:
	Camera *camera;
	RenderStage stage;

};
