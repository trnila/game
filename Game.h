#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include "Scene.h"

class Game {
public:
	void init() {
		glfwSetErrorCallback([] (int err, const char* description) -> void {
			throw std::runtime_error(description);
		});

		if (!glfwInit()) {
			throw std::runtime_error("failed to init glfw");
		}
		window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);
		if (!window) {
			glfwTerminate();
			throw std::runtime_error("could not create window");
		}

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		
		//glfwSetKeyCallback(window, key_callback);
		//glfwSetCursorPosCallback(window, cursor_callback);
		//glfwSetMouseButtonCallback(window, button_callback);
		glfwSetWindowSizeCallback(window, [] (GLFWwindow* window, int width, int height) -> void {
			glViewport(0, 0, width, height);
		});


		GLenum err = glewInit();
		if (err != GLEW_OK) {
			throw std::runtime_error("Could not initialize glew");
		}
		if (!GLEW_VERSION_3_3) {
			throw std::runtime_error("At least GLEW 3.3 is required");
		}

		glEnable(GL_DEPTH_TEST);

		
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		float ratio = width / (float)height;
		glViewport(0, 0, width, height);

		scene = new Scene(window);
	}



	void start() {
		while (!glfwWindowShouldClose(window)) {
			scene->renderOneFrame();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

private:
	GLFWwindow* window;
	Scene *scene;
};
