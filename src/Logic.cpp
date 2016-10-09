#include "Logic.h"

void RotateLogic::update(float diff) {
	obj.addAngle(anglePerSec * diff);
}

void TreeLogic::update(float diff) {
	if (obj.getScale().x > maxScale) {
		obj.rotate(90, 0, 0, 1);
		currentDeadTime += diff;

		if (currentDeadTime > deadTime) {
			obj.rotate(0, 0, 0, 1);
			obj.setScale(0.001, 0.001, 0.001);
			currentDeadTime = 0;
		}
	} else {
		obj.multiplyScale(growSpeed, growSpeed, growSpeed);
	}
}
