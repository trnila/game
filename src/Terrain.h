#pragma once
#include "Graphics/Program.h"
#include "Graphics/VBO.h"
#include "Graphics/VAO.h"
#include "Transformable.h"
class Scene;

struct Data {
	glm::vec3 points;
	glm::vec3 normal;
	glm::vec2 uvcoord;
};

class Terrain {
public:
	Terrain();
	~Terrain();

	void init();
	void draw(Scene &scene);
	float getHeightAt(float x, float z) {
		glm::vec4 pos = glm::vec4(x, 0, z, 1) * glm::inverse(t.getTransform());

		x = pos.x;
		z = pos.z;

		float val = 0;

		int n = 5;
		int X = (int) x;
		int Y = (int) z;
		for(int i = -n; i < n; i++) {
			for(int j = -n; j < n; j++) {
				x = X + i;
				z = Y + j;
				if(x >= 0 && x < this->width && z >=0 && z< this->height) {
					val = std::max(val, grid[(int) x][(int) z].points.y);
				}
			}
		}

		printf("%d %d = %f\n", (int)x, (int) z, val);
		fflush(stdout);
		return val * t.getScale().y;
	}

	Transformable& getTransform() {
		return t;
	}

	int getWidth() const;

	int getHeight() const;

protected:
	virtual void createTerrain();
	void createGrid(int width, int height);

	Data **grid;
private:
	Program prog;
	Texture *grass;
	Texture *dirt;
	Transformable t;
	int width, height;
	VBO vbo;

	void createShader();
	void loadTextures();
	void prepareForGpu();
	void calculateNormals();
};


