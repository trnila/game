#pragma once

#include "Object.h"

class Object;

class Logic {
public:
	Logic(Object &obj) : obj(obj) {}

	virtual void update(float diff) = 0;

protected:
	Object &obj;
};

class RotateLogic : public Logic {
public:
	RotateLogic(Object &obj, float angle) : Logic(obj), anglePerSec(angle) {}

	virtual void update(float diff);

private:
	float anglePerSec;
};

class TreeLogic : public Logic {
public:
	TreeLogic(Object &obj, float growSpeed, float maxScale, float deadTime) : Logic(obj), growSpeed(growSpeed),
	                                                                          maxScale(maxScale), deadTime(deadTime) {}


	virtual void update(float diff);

private:
	float deadTime;
	float growSpeed;
	float maxScale;
	float currentDeadTime = 0;
};