#pragma once

#include "Program.h"

class Skybox {
public:
	Skybox();

	void render(Camera camera);

private:
	Program program;
	GLuint textureID;
	GLuint skyboxVAO, skyboxVBO;
};


