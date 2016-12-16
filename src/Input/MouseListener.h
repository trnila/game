#pragma once

class MouseListener {
public:
	virtual void onMove(double x, double y) = 0;
	virtual void onClick(int button, int action, double x, double y) {}
};