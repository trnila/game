#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "VBO.h"
#include "Program.h"
#include "data.h"

class Object {
public:
	glm::mat4 getTransform() {
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
			glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), rotateAround);

		return model * anim;
	}

	void move(float x, float y, float z) {
		position.x += x;
		position.y += y;
		position.z += z;
	}

	void setPosition(float x, float y, float z) {
		position = glm::vec3(x, y, z);
	}

	void rotate(float angle, float x, float y, float z) {
		this->angle = angle;
		rotateAround = glm::vec3(x, y, z);
	}

	void setAngle(float angle) {
		this->angle = angle;
	}

	void addAngle(float angle) {
		this->angle += angle;
	}

	VBO vbo;
	VBO colorbuffer;
private:
	glm::vec3 position;
	glm::vec3 rotateAround;
	float angle;


};

class Scene {
public:
	Scene(GLFWwindow *window) {
		init_resources();

		objects.emplace_back(Object());
		objects.emplace_back(Object());

		objects[0].setPosition(0, 0, -4);
		objects[0].rotate(0, 0, 1, 0);
		
		objects[1].setPosition(0, 0, -9);
		objects[1].rotate(0, 0, -1, 0);

		obj = &objects[0];
		obj->vbo.setData((const char*) points, sizeof(points));

		vao.bind();
		vao.enableAttrib(0);

		obj->vbo.bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		obj->colorbuffer.bind();
		obj->colorbuffer.setData((const char*) g_color_buffer_data, sizeof(g_color_buffer_data));
		glEnableVertexAttribArray(1);
		obj->colorbuffer.bind();
		glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, (void*) 0);


		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
		view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
		projection = glm::perspective(45.0f, 1.0f*width/height, 0.1f, 10.0f);

		// todo: fix!
		mvpVar = prog.bindUniformVariable("mvp");

		objects[1].vbo = objects[0].vbo;

	}
	
	int init_resources() {
		try {
			Shader vertex(GL_VERTEX_SHADER, "triangle.v.glsl");
			Shader fragment(GL_FRAGMENT_SHADER, "triangle.f.glsl");

			prog.attach(vertex);
			prog.attach(fragment);
			prog.link();

		} catch(GlslCompileError &err) {
			std::cerr << "GLSL error: " << err.getSource() << " - " << err.what() << "\n";
		}

		return 1;
	}

	void update(float time) {
		float angle = time * 45;

		objects[0].addAngle(angle);
		objects[1].addAngle(angle);
	}

	void renderOneFrame() {
		glClearColor(.0, .0, .0, .0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for(Object &o: objects) {
			glm::mat4 mvp = projection * view * o.getTransform();

			prog.use();

			mvpVar->setData(mvp);

			vao.bind();
			glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		}
	}

private:
	VAO vao;
	Program prog;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	UniformVariable *mvpVar;

	Object *obj;
	std::vector<Object> objects;
};
