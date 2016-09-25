#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "Program.h"
#include "Object.h"
#include "data.h"


class Scene {
public:
	Scene(GLFWwindow *window) {
		init_resources();

		objects.emplace_back(Object());
		objects.emplace_back(Object());
		objects.emplace_back(Object());

		objects[0].setPosition(-1, 0, -4);
		objects[0].rotate(0, 0, 1, 0);
		objects[0].renderable = new Model(triangleVertices, triangleRed, 3);
		
		objects[1].setPosition(0, 0, -9);
		objects[1].rotate(0, 0, -1, 0);
		objects[1].renderable = new Model(cubeVertices, cubeRandColors, 36);

		objects[2].setPosition(2, 0, -3);
		objects[2].rotate(0, 0, 1, 0);
		objects[2].renderable = new Model(triangleVertices, triangleBlue, 3);


		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -6.0));
		view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));// * glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -8.0));
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

		for(Object &o: objects) {
			o.addAngle(angle);
		}
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
