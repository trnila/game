#pragma once


#include "BaseLight.h"

class PointLight: public BaseLight {
public:
	PointLight(Scene &shader, int id);
};


