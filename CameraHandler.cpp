#include "Scene.h"

CameraHandler::CameraHandler(Camera *camera) : camera(camera), vertChange(0), horChange(0) {}

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
	horChange = lastX - x;
	vertChange = lastY - y;

	lastX = x;
	lastY = y;
}
