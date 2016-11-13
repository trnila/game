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
	Image image("resources/5.png", 1);
	x = image.getWidth();
	y = image.getHeight();


	glm::vec3 map[x][y];
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			map[i][j] = glm::vec3(i , image[i * x + j], j);
		}
	}

	float fTextureU = float(x) * 0.05f;
	float fTextureV = float(y) * 0.05f;

	Data grid[x][y];
	for(int j = 0; j < y - 1; j++) {
		for(int i = 0; i < x; i++) {
			float fScaleC = float(j)/float(x - 1);
			float fScaleR = float(i)/float(y - 1);

			grid[i][j].points = map[i][j];
			grid[i][j].uvcoord = glm::vec2(fTextureU * fScaleC, fTextureV * fScaleR);
		}
	}

	auto norm = [](Data &a, Data &b, Data &c) -> glm::vec3 {
		return cross(a.points - b.points, c.points - b.points);
	};

	for(int j = 0; j < y - 1; j++) {
		for(int i = 0; i < x; i++) {
			int points[][2] = {
					{-1, 0}, {0, -1}, {1, 0}, {0, 1}
			};


			grid[i][j].normal = glm::vec3(0);
			for(int k = 0; k < 4; k++) {
				int *a = points[k];
				int *b = points[(k + 1) % 4];

				grid[i][j].normal -= norm(grid[i + a[0]][j + a[1]], grid[i][j], grid[i + b[0]][j + b[0]]);
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
}

void Terrain::loadTextures() {
	grass = new Texture("resources/grass.jpg");
	dirt = new Texture("resources/rocks.jpg");
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
	prog.updated(*scene.getRootNode().getLight(0));

	auto obj = vbo.activate();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for(int i = 0; i < y; i++) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) (sizeof(Data) * 2 * x * i));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) (sizeof(Data) * 2 * x * i) + (sizeof(float) * 3));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) (sizeof(Data) * 2 * x * i) + (sizeof(float) * 6));

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 2 * x);
	}
}
