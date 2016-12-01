#include "Utils/ResourceManager.h"
#include "Terrain.h"
#include <GL/glew.h>
#include <glm/ext.hpp>
#include "Graphics/Texture.h"
#include "Transformable.h"
#include "Utils/Image.h"
#include "Graphics/Material.h"
#include "Scene.h"

Terrain::Terrain(Mediator &mediator) {
	createShader();
	mediator.registerProgram(&prog);
	loadTextures();
	init();
}

void Terrain::init() {
	createTerrain();
	this->calculateNormals();
	this->prepareForGpu();
}

void Terrain::createTerrain() {
	Image image("resources/heightmaps/5.png", 1);
	createGrid(image.getWidth(), image.getHeight());

	float fTextureU = float(width) * 0.1f;
	float fTextureV = float(height) * 0.1f;

	for(int j = 0; j < height; j++) {
		for(int i = 0; i < width; i++) {
			Data &point = grid[i][j];

			float fScaleC = float(j)/float(width - 1);
			float fScaleR = float(i)/float(height - 1);

			//glm::vec2 c = 4.0f * glm::vec2(fScaleC, fScaleR);
			//const float d = 0.5f + 0.5f*glm::perlin(c);

			point.points = glm::vec3(i , image[i * width + j], j);
			//grid[i][j].points = glm::vec3(i , 80*d, j);

			point.uvcoord = glm::vec2(fTextureU * fScaleC, fTextureV * fScaleR);
		}
	}
}

void Terrain::createGrid(int width, int height) {
	this->width = width;
	this->height = height;
	grid = new Data*[width];
	for (int i = 0; i < width; i++) {
		grid[i] = new Data[height];
	}
}

void Terrain::calculateNormals() {
	auto norm = [](Data &a, Data &b, Data &c) -> glm::vec3 {
		return cross(a.points - b.points, c.points - b.points);
	};

	auto inRange = [](int x, int max) -> bool {
		return x >= 0 && x < max;
	};

	for(int j = 0; j < height - 1; j++) {
		for(int i = 0; i < width - 1; i++) {
			int points[][2] = {
					{-1, 0}, {0, -1}, {1, 0}, {0, 1}
			};


			grid[i][j].normal = glm::vec3(0);
			for(int k = 0; k < 4; k++) {
				int *a = points[k];
				int *b = points[(k + 1) % 4];

				if (inRange(i+a[0], width) && inRange(i + b[0], width) && inRange(j + a[0], height) && inRange(j + b[0], height)) {
					grid[i][j].normal -= norm(grid[i + a[0]][j + a[1]], grid[i][j], grid[i + b[0]][j + b[0]]);
				}
			}
		}
	}
}

void Terrain::prepareForGpu() {
	std::vector<Data> points;
	for(int j = 0; j < height - 1; j++) {
		for(int i = 0; i < width; i++) {
			points.push_back(grid[i][j + 1]);
			points.push_back(grid[i][j]);
		}
	}

	auto obj = vbo.activate();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Data) * points.size(), points.data(), GL_STATIC_DRAW);
}

void Terrain::loadTextures() {
	grass = new Texture("resources/heightmaps/grass.jpg");
	dirt = new Texture("resources/heightmaps/rocks.jpg");
	snow = new Texture("resources/snow.jpg");
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
	prog.useTexture("snow", *snow, 2);
	prog.send("modelMatrix", t.getTransform());
	Material material;
	material.specularColor = Color(0);
	material.apply(prog);

	auto obj = vbo.activate();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for(int i = 0; i < height; i++) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) (sizeof(Data) * 2 * width * i));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) ((sizeof(Data) * 2 * width * i) + (sizeof(float) * 3)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) ((sizeof(Data) * 2 * width * i) + (sizeof(float) * 6)));

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 2 * width);
	}
}

Terrain::~Terrain() {
	deleteGrid();
}

void Terrain::deleteGrid() {
	for (int i = 0; i < width; i++) {
		delete[] grid[i];
	}
	delete[] grid;
	grid = nullptr;
}

int Terrain::getWidth() const {
	return width;
}

int Terrain::getHeight() const {
	return height;
}
