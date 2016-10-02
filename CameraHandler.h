#pragma once

#include "Camera.h"
#include "Object.h"
#include "KeyListener.h"
#include "MouseListener.h"

class CameraHandler : public KeyListener, public MouseListener {
public:
	CameraHandler(Camera *camera);
	virtual void onKey(int key, int scancode, int action, int mods) override;

	virtual void onMove(double x, double y) override;
	void update(float time);

private:
	Camera *camera;
	double horChange;
	double vertChange;
	bool forward = false;
	bool backward = false;
};


