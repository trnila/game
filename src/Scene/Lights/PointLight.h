#pragma once


#include "BaseLight.h"

class PointLight: public BaseLight {
public:
	PointLight(Program &shader, int id);
};


