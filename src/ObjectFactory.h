#pragma once

#include "Program.h"
#include "Object.h"

class ObjectFactory {
public:
	ObjectFactory(Program &shader, Program &shadower);

	Object* create(const char *name);


private:
	Program &shader, &shadower;
};


