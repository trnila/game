#include "Utils/ResourceManager.h"
#include "Terrain.h"
#include <GL/glew.h>
#include <glm/ext.hpp>
#include "Graphics/Texture.h"
#include "Transformable.h"
#include "Utils/Image.h"
#include "Graphics/Material.h"
#include "Scene.h"

Terrain::Terrain(Scene &scene) {
	createShader();
	scene.registerProgram(&prog);
	scene.getActiveCamera().addListener(&prog);
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

	float fTextureU = float(getWidth()) * 0.1f;
	float fTextureV = float(getHeight()) * 0.1f;

	for(int j = 0; j < getHeight(); j++) {
		for(int i = 0; i < getWidth(); i++) {
			Data &point = grid->at(i, j);

			float fScaleC = float(j)/float(getWidth() - 1);
			float fScaleR = float(i)/float(getHeight() - 1);

			point.points = glm::vec3(i , image[i * getWidth() + j], j);
			point.uvcoord = glm::vec2(fTextureU * fScaleC, fTextureV * fScaleR);
		}
	}
}

void Terrain::createGrid(int width, int height) {
	grid = new Matrix<Data>(width, height);
}

void Terrain::calculateNormals() {
	auto norm = [](Data &a, Data &b, Data &c) -> glm::vec3 {
		return cross(a.points - b.points, c.points - b.points);
	};

	auto inRange = [](int x, int max) -> bool {
		return x >= 0 && x < max;
	};

	for(int j = 0; j < getHeight()- 1; j++) {
		for(int i = 0; i < getWidth() - 1; i++) {
			int points[][2] = {
					{-1, 0}, {0, -1}, {1, 0}, {0, 1}
			};


			grid->at(i, j).normal = glm::vec3(0);
			for(int k = 0; k < 4; k++) {
				int *a = points[k];
				int *b = points[(k + 1) % 4];

				if (inRange(i+a[0], getWidth()) && inRange(i + b[0], getWidth()) && inRange(j + a[1], getHeight()) && inRange(j + b[0], getHeight())) {
					grid->at(i, j).normal -= norm(grid->at(i + a[0], j + a[1]), grid->at(i, j), grid->at(i + b[0], j + b[0]));
				}
			}
		}
	}
}

void Terrain::prepareForGpu() {
	std::vector<Data> points;
	for(int j = 0; j < getHeight() - 1; j++) {
		for(int i = 0; i < getWidth(); i++) {
			points.push_back(grid->at(i, j + 1));
			points.push_back(grid->at(i, j));
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

void Terrain::drawPrimitive() {
	auto obj = vbo.activate();
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glEnableVertexAttribArray(1));
	GL_CHECK(glEnableVertexAttribArray(2));

	for(int i = 0; i < getHeight(); i++) {
		GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) (sizeof(Data) * 2 * getWidth() * i)));
		GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) ((sizeof(Data) * 2 * getWidth() * i) + (sizeof(float) * 3))));
		GL_CHECK(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) ((sizeof(Data) * 2 * getWidth() * i) + (sizeof(float) * 6))));

		GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 2 * getWidth()));
	}
}

Terrain::~Terrain() {
	delete grid;
}

int Terrain::getWidth() const {
	return grid->getCols();
}

int Terrain::getHeight() const {
	return grid->getRows();
}

void Terrain::drawShadows() {
	drawPrimitive();
}

void Terrain::render(RenderContext &context) {
	context.applyShadows(prog);
	if(context.getStage() == RenderStage::Shadow) {
		drawShadows();
	} else {
		prog.use();
		prog.useTexture("grass", *grass, 0);
		prog.useTexture("dirt", *dirt, 1);
		prog.useTexture("snow", *snow, 2);
		prog.send("modelMatrix", getTransform());
		Material material;
		material.specularColor = Color(0);
		material.apply(prog);

		drawPrimitive();
	}
}

Object *Terrain::find(int id) {
	return nullptr;
}
