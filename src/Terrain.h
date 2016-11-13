
#pragma once


#include "Graphics/Program.h"
#include "Graphics/VBO.h"
#include "Graphics/VAO.h"
#include "Transformable.h"
class Scene;

class Terrain {
public:
	Terrain();
	void draw(Scene &scene);

	Transformable& getTransform() {
		return t;
	}

private:
	Program prog;
	Texture *grass;
	Texture *dirt;
	Transformable t;
	int x, y;
	VBO vbo;

	void createShader();
	void loadTextures();
	void createTerrain();
};


