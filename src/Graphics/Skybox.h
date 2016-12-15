#pragma once

#include "Program.h"
#include "Texture.h"
#include "CubeMap.h"
#include "VAO.h"
#include "VBO.h"
#include "Model.h"

class Skybox: public Node {
public:
	Skybox(const std::vector<std::string> &faces);
	Skybox(const char *prefix);
	~Skybox();

	void render(RenderContext &c);

	Object *find(int id) override;

	Program program;
private:
	CubeMap* cubemap;
	Model *model;

	void load(const std::vector<std::string> &faces);
};


