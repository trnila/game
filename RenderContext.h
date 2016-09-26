#pragma once
#include "Program.h"
#include "VBO.h"
#include "VAO.h"
#include "Camera.h"

class RenderContext {
public:
	void use(Program& program) {
		program.use();
	}

	void bind(VAO &vao) {
		vao.bind();
	}

	void bind(VBO &vbo) {
		vbo.bind();
	}

	void clearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void clear(int flags) {
		glClear(flags);
	}

	void drawArrays(int type, int start, int stop) {
		glDrawArrays(type, start, stop);
	}

	void setCamera(Camera *camera) {
		this->camera = camera;
	}

	Camera* getCamera() {
		return camera;
	}
private:
	Camera *camera;
};
