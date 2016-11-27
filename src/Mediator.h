#pragma once

#include "Graphics/Program.h"

class Mediator {
public:
	void registerProgram(Program *program) {
		programs.push_back(program);
	}

	void lightChanged(BaseLight *light) {
		for(Program* program: programs) {
			program->updated(*light);
		}
	}

private:
	std::vector<Program*> programs;
};


