#include "Utils/ResourceManager.h"
#include "Terrain.h"
#include "stb_image.h"
#include <GL/glew.h>
#include <stdlib.h>

GLuint vao, vbo;
int n;

struct Data {
	glm::vec3 points;
	glm::vec3 color;
};
std::vector<Data> points;
Terrain::Terrain() {
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/terrain.v.glsl", GL_VERTEX_SHADER));
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/terrain.f.glsl", GL_FRAGMENT_SHADER));
	prog.link();
	prog.use();

	int x,y,n;
	unsigned char *data = stbi_load("resources/heightmap.jpg", &x, &y, &n, 1);
	if(!data) {
		abort();
	}

	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data));

	/*for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			points.push_back(glm::vec3(i*100, 10, j * 100));
		}
	}*/

	glm::vec3 map[10][10];
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			map[i][j] = glm::vec3(i*10 , i % 2 == 0, j*10 );
		}
	}



	int j = 0;
	for(int i = 0; i < 10; i++) {
		Data a;
		a.points = map[i][j + 1];
		a.color = glm::vec3(1, 1, 1);
		points.push_back(a);


		a.points = map[i][j];
		a.color = glm::vec3(1, 0, 1);
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
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Data),                  // stride
			(void*)0            // array buffer offset
	);
	glVertexAttribPointer(
			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Data),                  // stride
			(void*)(sizeof(float)*3)            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, points.size());
	glDisableVertexAttribArray(0);
}
