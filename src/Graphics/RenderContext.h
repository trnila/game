#pragma once
#include "VBO.h"
#include "VAO.h"

enum class RenderStage {
	Shadow,
	Normal
};

class RenderContext {
public:
	void clearColor(float r, float g, float b, float a) {
		GL_CHECK(glClearColor(r, g, b, a));
	}

	void clear(int flags) {
		GL_CHECK(glClear(flags));
	}

	RenderStage getStage() const {
		return stage;
	}

	void setStage(RenderStage stage) {
		this->stage = stage;
	}

private:
	RenderStage stage;
};
