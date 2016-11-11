#include "Utils/ResourceManager.h"
#include "Terrain.h"
#include "stb_image.h"
#include <GL/glew.h>
#include <stdlib.h>
#include "Graphics/Texture.h"

GLuint vao, vbo;
int n;
int x, y;

struct Data {
	glm::vec3 points;
	glm::vec3 normal;
	glm::vec2 uvcoord;
};
std::vector<Data> points;
Texture *grass;
Texture *dirt;
Terrain::Terrain() {
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/terrain.v.glsl", GL_VERTEX_SHADER));
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/terrain.f.glsl", GL_FRAGMENT_SHADER));
	prog.link();
	prog.use();

	//unsigned char *data = stbi_load("resources/heightmap.jpg", &x, &y, &n, 1);
	unsigned char *data = stbi_load("resources/5.png", &x, &y, &n, 1);
	if(!data) {
		abort();
	}


	glm::vec3 map[x][y];
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			map[i][j] = glm::vec3(i*10 , data[i * x + j], j*10 );
		}
	}



	grass = new Texture("resources/grass.jpg");
	dirt = new Texture("resources/rocks.jpg");
	float fTextureU = float(x)*0.1f;
	float fTextureV = float(y)*0.1f;

	for(int j = 0; j < y-1; j++)
	for(int i = 0; i < x; i++) {

		float fScaleC = float(j)/float(x-1);
		float fScaleR = float(i)/float(y-1);
		Data a;
		a.points = map[i][j + 1];
		a.uvcoord = glm::vec2(fTextureU*fScaleC, fTextureV*fScaleR);
		//a.normal = glm::cross(map[i][j] - map[i][j + 1], map[i+1][j + 1] - map[i][j + 1]);
		a.normal = glm::vec3(17, 45, 0);

		points.push_back(a);


		fScaleC = float(j+1)/float(x-1);
		fScaleR = float(i)/float(y-1);
		a.points = map[i][j];
		a.uvcoord = glm::vec2(fTextureU*fScaleC, fTextureV*fScaleR);
		a.normal = glm::vec3(45, 18, 0);
		points.push_back(a);
	}




	glGenBuffers(1, &vbo);
// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Data) * points.size(), points.data(), GL_STATIC_DRAW);
}

void Terrain::draw(Camera &cam) {
	prog.use();
	prog.updated(cam);
	//auto v3 = vao.activate();


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	prog.useTexture("grass", *grass, 0);
	prog.useTexture("dirt", *dirt, 1);

	for(int i = 0; i < y; i++) {
		glVertexAttribPointer(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				sizeof(Data),
				(void *) (sizeof(Data)*2*x*i)
		);
		glVertexAttribPointer(
				1,
				3,
				GL_FLOAT,
				GL_FALSE,
				sizeof(Data),
				(void *) (sizeof(Data)*2*x*i)+(sizeof(float) * 3)
		);
		glVertexAttribPointer(
				2,
				2,
				GL_FLOAT,
				GL_FALSE,
				sizeof(Data),
				(void *) (sizeof(Data)*2*x*i)+(sizeof(float) * 6)
		);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 2*x);
	}
	glDisableVertexAttribArray(0);
}
