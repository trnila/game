#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "VBO.h"
#include "Program.h"
#include "data.h"


class Scene {
public:
	Scene(GLFWwindow *window) {
		init_resources();

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

	void renderOneFrame() {
			float angle = glfwGetTime() * 45;
			glm::vec3 axis_y(0, 1, 0);
			glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_y);
			glm::mat4 mvp = projection * view * model * anim;

			glClearColor(.0, .0, .0, .0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			prog.use();

			mvpVar->setData(mvp);

			vao.bind();
			glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	}

private:
	VBO vbo, colorbuffer;
	VAO vao;
	Program prog;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	UniformVariable *mvpVar;
};
