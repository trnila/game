#include "Utils/ResourceManager.h"
#include "Terrain.h"
#include <GL/glew.h>
#include <stdlib.h>
#include "Graphics/Texture.h"
#include "Transformable.h"
#include "Utils/Image.h"
#include "Graphics/Material.h"
#include "Scene.h"

struct Data {
	glm::vec3 points;
	glm::vec3 normal;
	glm::vec2 uvcoord;
};

Terrain::Terrain() {
	createShader();
	loadTextures();
	createTerrain(); }

void Terrain::createTerrain() {
	Image image("resources/heightmaps/5.png", 1);
	x = image.getWidth();
	y = image.getHeight();

	float fTextureU = float(x) * 0.05f;
	float fTextureV = float(y) * 0.05f;

	//TODO: fix
	Data **grid = new Data*[x];
	for (int i = 0; i < x; i++) {
		grid[i] = new Data[y];
	}

	for(int j = 0; j < y; j++) {
		for(int i = 0; i < x; i++) {
			float fScaleC = float(j)/float(x - 1);
			float fScaleR = float(i)/float(y - 1);

			grid[i][j].points = glm::vec3(i , image[i * x + j], j);
			grid[i][j].uvcoord = glm::vec2(fTextureU * fScaleC, fTextureV * fScaleR);
		}
	}

	auto norm = [](Data &a, Data &b, Data &c) -> glm::vec3 {
		return cross(a.points - b.points, c.points - b.points);
	};

	auto inRange = [](int x, int max) -> bool {
		return x >= 0 && x < max;
	};

	for(int j = 0; j < y - 1; j++) {
		for(int i = 0; i < x - 1; i++) {
			int points[][2] = {
					{-1, 0}, {0, -1}, {1, 0}, {0, 1}
			};


			grid[i][j].normal = glm::vec3(0);
			for(int k = 0; k < 4; k++) {
				int *a = points[k];
				int *b = points[(k + 1) % 4];

				if (inRange(i+a[0], x) && inRange(i+b[0], x) && inRange(j+a[0], y) && inRange(j + b[0], y)) {
					grid[i][j].normal -= norm(grid[i + a[0]][j + a[1]], grid[i][j], grid[i + b[0]][j + b[0]]);
				}
			}
		}
	}

	std::vector<Data> points;
	for(int j = 0; j < y - 1; j++) {
		for(int i = 0; i < x; i++) {
			points.push_back(grid[i][j + 1]);
			points.push_back(grid[i][j]);
		}
	}

	auto obj = vbo.activate();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Data) * points.size(), points.data(), GL_STATIC_DRAW);

	for (int i = 0; i < x; i++) {
		delete[] grid[i];
	}
	delete[] grid;

}

void Terrain::loadTextures() {
	grass = new Texture("resources/heightmaps/grass.jpg");
	dirt = new Texture("resources/heightmaps/rocks.jpg");
}

void Terrain::createShader() {
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/terrain.v.glsl", GL_VERTEX_SHADER));
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/terrain.f.glsl", GL_FRAGMENT_SHADER));
	prog.link();
	prog.use();
}

void Terrain::draw(Scene &scene) {
	prog.use();
	prog.updated(scene.getActiveCamera());
	prog.useTexture("grass", *grass, 0);
	prog.useTexture("dirt", *dirt, 1);
	prog.send("modelMatrix", t.getTransform());
	Material material;
	material.specularColor = Color(0);
	material.apply(prog);

	for(int i = 0; i < 8; i++) {
		Light *light = scene.getRootNode().getLight(i);
		if(light) {
			prog.updated(*light);
		}
	}

	auto obj = vbo.activate();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for(int i = 0; i < y; i++) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) (sizeof(Data) * 2 * x * i));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) ((sizeof(Data) * 2 * x * i) + (sizeof(float) * 3)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) ((sizeof(Data) * 2 * x * i) + (sizeof(float) * 6)));

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 2 * x);
	}
}
