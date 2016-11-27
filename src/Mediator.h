#pragma once

#include "Graphics/Program.h"
#include "ObjectFactory.h"

class Mediator {
public:
	Mediator(ObjectFactory *factory) : factory(factory) {}

	void registerProgram(Program *program) {
		programs.push_back(program);
	}

	void lightChanged(BaseLight *light) {
		for(Program* program: programs) {
			program->updated(*light);
		}
	}

	void setAmbientLight(Color color) {
		for(Program* program: programs) {
			program->setAmbientColor(color);
		}
	}

	ObjectFactory* getObjectFactory() {
		return factory;
	}
private:
	std::vector<Program*> programs;
	ObjectFactory* factory;
};


