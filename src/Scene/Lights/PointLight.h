#pragma once


#include "BaseLight.h"

class PointLight: public BaseLight {
public:
	PointLight(Mediator &shader, int id);
};


