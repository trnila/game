#pragma once

#include "Camera.h"
#include "Object.h"
#include "../Input/KeyListener.h"
#include "../Input/MouseListener.h"

class CameraHandler : public KeyListener, public MouseListener {
public:
	CameraHandler(Camera *camera);

	virtual void onKey(int key, int scancode, int action, int mods) override;
	virtual void onMove(double x, double y) override;

	void operator()(Node& node, float dt, Scene& scene);

private:
	Camera *camera;
	double horChange;
	double vertChange;
	bool forward = false;
	bool backward = false;
	bool right = false;
	bool left = false;

	double lastX, lastY;
};


