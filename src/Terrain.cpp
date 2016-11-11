#include "Utils/ResourceManager.h"
#include "Terrain.h"
#include <GL/glew.h>
#include <stdlib.h>
#include "Graphics/Texture.h"
#include "Transformable.h"
#include "Utils/Image.h"

struct Data {
	glm::vec3 points;
	glm::vec3 normal;
	glm::vec2 uvcoord;
};

Terrain::Terrain() {
	createShader();
	loadTextures();
	createTerrain();
	t.setScale(10, 1, 10);
}

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


	float fTextureU = float(x) * 0.1f;
	float fTextureV = float(y) * 0.1f;

	std::vector<Data> points;
	for(int j = 0; j < y - 1; j++)
	for(int i = 0; i < x; i++) {

		float fScaleC = float(j)/float(x - 1);
		float fScaleR = float(i)/float(y - 1);
		Data a;
		a.points = map[i][j + 1];
		a.uvcoord = glm::vec2(fTextureU * fScaleC, fTextureV * fScaleR);
		//a.normal = glm::cross(map[i][j] - map[i][j + 1], map[i+1][j + 1] - map[i][j + 1]);
		a.normal = glm::vec3(17, 45, 0);

		points.push_back(a);


		fScaleC = float(j+1)/float(x - 1);
		fScaleR = float(i)/float(y - 1);
		a.points = map[i][j];
		a.uvcoord = glm::vec2(fTextureU * fScaleC, fTextureV * fScaleR);
		a.normal = glm::vec3(45, 18, 0);
		points.push_back(a);
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

void Terrain::draw(Camera &cam) {
	prog.use();
	prog.updated(cam);

	auto obj = vbo.activate();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	prog.useTexture("grass", *grass, 0);
	prog.useTexture("dirt", *dirt, 1);
	prog.send("modelMatrix", t.getTransform());

	for(int i = 0; i < y; i++) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) (sizeof(Data) * 2 * x * i));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) (sizeof(Data) * 2 * x * i) + (sizeof(float) * 3));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Data), (void *) (sizeof(Data) * 2 * x * i) + (sizeof(float) * 6));

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 2 * x);
	}
}
