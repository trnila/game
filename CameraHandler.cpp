#include "Scene.h"

CameraHandler::CameraHandler(Camera *camera) :
		camera(camera),
		horChange(0),
		vertChange(0),
		lastX(0),
		lastY(0) {}

void CameraHandler::update(float time) {
	double mouseSpeed = time;
	camera->rotateBy(mouseSpeed * vertChange, mouseSpeed * horChange);
	horChange = vertChange = 0;

	float speed = 5 * time;
	if (forward) {
		camera->forward(speed);
	}
	if (backward) {
		camera->backward(speed);
	}
	if (right) {
		camera->right(speed);
	}
	if (left) {
		camera->left(speed);
	}
}

void CameraHandler::onKey(int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_UP) {
			forward = true;
		} else if (key == GLFW_KEY_DOWN) {
			backward = true;
		} else if (key == GLFW_KEY_RIGHT) {
			right = true;
		} else if (key == GLFW_KEY_LEFT) {
			left = true;
		}
	} else if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_UP) {
			forward = false;
		} else if (key == GLFW_KEY_DOWN) {
			backward = false;
		} else if (key == GLFW_KEY_RIGHT) {
			right = false;
		} else if (key == GLFW_KEY_LEFT) {
			left = false;
		}
	}
}

void CameraHandler::onMove(GLFWwindow *window, double x, double y) {
	horChange = lastX - x;
	vertChange = lastY - y;

	lastX = x;
	lastY = y;
}
