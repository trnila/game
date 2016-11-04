#pragma once

#include "Graphics/Program.h"
#include "Scene/Object.h"

class ObjectFactory {
public:
	ObjectFactory(Program &shader, Program &shadower);

	Object* create(const char *name);


private:
	Program &shader, &shadower;
	int lastId = -1;
};


