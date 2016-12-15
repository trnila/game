#pragma once
#include "Graphics/Program.h"
#include "Graphics/VBO.h"
#include "Graphics/VAO.h"
#include "Transformable.h"
#include "Mediator.h"
#include "Utils/Matrix.h"

class Scene;

struct Data {
	glm::vec3 points;
	glm::vec3 normal;
	glm::vec2 uvcoord;
};

class Terrain {
public:
	Terrain(Mediator &mediator);
	~Terrain();

	void init();
	void draw(Scene &scene);
	virtual float getHeightAt(float x, float z) {
		glm::vec4 pos = glm::vec4(x, 0, z, 1) * glm::inverse(t.getTransform());

		x = pos.x;
		z = pos.z;

		float val = 0;

		int n = 7;
		int X = (int) x;
		int Y = (int) z;
		for(int i = -n; i < n; i++) {
			for(int j = -n; j < n; j++) {
				x = X + i;
				z = Y + j;
				if(x >= 0 && x < getWidth() && z >=0 && z< getHeight()) {
					val = std::max(val, grid->at(x, z).points.y);
				}
			}
		}

		return val * t.getScale().y;
	}

	Transformable& getTransform() {
		return t;
	}

	int getWidth() const;

	int getHeight() const;

	Program prog;
protected:
	virtual void createTerrain();
	void createGrid(int width, int height);

	Matrix<Data> *grid;
private:
	Texture *grass;
	Texture *dirt;
	Texture *snow;
	Transformable t;
	VBO vbo;

	void createShader();
	void loadTextures();
	void prepareForGpu();
	void calculateNormals();
};


