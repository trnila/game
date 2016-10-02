#include "Scene.h"

CameraHandler::CameraHandler(Camera *camera) : camera(camera) {}

void CameraHandler::update(float time) {
	double mouseSpeed = time;
	camera->rotateBy(mouseSpeed * vertChange, mouseSpeed * horChange);
	horChange = vertChange = 0;

	if (forward) {
		camera->move(0, 0, -10 * time);
	} else if (backward) {
		camera->move(0, 0, 10 * time);
	}
}

void CameraHandler::onKey(int key, int scancode, int action, int mods) {
	forward = backward = false;
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_UP) {
			forward = true;
		} else if (key == GLFW_KEY_DOWN) {
			backward = true;
		}
	}
}

void CameraHandler::onMove(GLFWwindow *window, double x, double y) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	horChange = float(width / 2 - x);
	vertChange = float(height / 2 - y);
	glfwSetCursorPos(window, width / 2, height / 2);
}