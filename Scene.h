#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "VBO.h"
#include "Program.h"
#include "data.h"


class Renderable {
public:
	virtual void render() = 0;

};

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

	Renderable *renderable;
	
private:
	glm::vec3 position;
	glm::vec3 rotateAround;
	float angle;
};

class Box: public Renderable { 
public:
	Box() {
		vbo.setData((const char*) points, sizeof(points));

		vao.bind();
		vao.enableAttrib(0);

		vbo.bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		colorbuffer.bind();
		colorbuffer.setData((const char*) g_color_buffer_data, sizeof(g_color_buffer_data));
		glEnableVertexAttribArray(1);
		colorbuffer.bind();
		glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE, 0, (void*) 0);
	}

	virtual void render() {
		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	}

private:
	VBO vbo, colorbuffer;
	VAO vao;
};

class Rect: public Renderable {
public:
	Rect() {
		float data[] = {
			-1.0, -1.0, 0.0,
			1.0, -1.0, 0.0,
			-1.0, 1.0, 1.0
		};

		float colors[] = {
			1.0, 0, 0,
			1.0, 0, 0,
			1.0, 0, 0,
		//	0, 1, 0,
		//	0, 0, 1
		};

		vao.bind();
		vao.enableAttrib(0);

		vbo.bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		vbo.setData((const char*) data, sizeof(data));

		colorsVbo.bind();
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		colorsVbo.setData((const char*) colors, sizeof(colors));
		glEnableVertexAttribArray(1);

	}

	virtual void render() {
		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
private:
	VBO vbo, colorsVbo;
	VAO vao;
};

class Scene {
public:
	Scene(GLFWwindow *window) {
		init_resources();

		objects.emplace_back(Object());
		objects.emplace_back(Object());

		objects[0].setPosition(0, 0, -4);
		objects[0].rotate(0, 0, 1, 0);
		objects[0].renderable = new Rect();
		
		objects[1].setPosition(0, 0, -9);
		objects[1].rotate(0, 0, -1, 0);
		objects[1].renderable = new Box();


		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
		view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
		projection = glm::perspective(45.0f, 1.0f*width/height, 0.1f, 10.0f);

		// todo: fix!
		mvpVar = prog.bindUniformVariable("mvp");

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

		//objects[0].addAngle(angle);
		//objects[1].addAngle(angle);
	}

	void renderOneFrame() {
		glClearColor(.0, .0, .0, .0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		prog.use();

		for(Object &o: objects) {
			glm::mat4 mvp = projection * view * o.getTransform();
			mvpVar->setData(mvp);
			o.renderable->render();
		}
	}

private:
	Program prog;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	UniformVariable *mvpVar;

	std::vector<Object> objects;
};
