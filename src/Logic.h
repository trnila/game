#pragma once

#include "Object.h"

class Object;

class Logic {
public:
	Logic(Node &obj) : obj(obj) {}

	virtual void update(float diff) = 0;

protected:
	Node &obj;
};

class RotateLogic : public Logic {
public:
	RotateLogic(Node &obj, float angle) : Logic(obj), anglePerSec(angle) {}

	virtual void update(float diff);

private:
	float anglePerSec;
};

class TreeLogic : public Logic {
public:
	TreeLogic(Node &obj, float growSpeed, float maxScale, float deadTime) : Logic(obj), growSpeed(growSpeed),
	                                                                        maxScale(maxScale), deadTime(deadTime) {}


	virtual void update(float diff);

private:
	float deadTime;
	float growSpeed;
	float maxScale;
	float currentDeadTime = 0;
};

class MoveLogic: public Logic {
public:
	MoveLogic(Node &obj);

	virtual void update(float diff) override;

};

class FollowLogic: public Logic {
public:
	FollowLogic(Node &obj, Camera *cam);

	virtual void update(float diff) override;

private:
	Camera *cam;
};