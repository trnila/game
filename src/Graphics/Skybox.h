#pragma once

#include "Program.h"
#include "Texture.h"
#include "CubeMap.h"
#include "VAO.h"
#include "VBO.h"
#include "Model.h"

class Skybox: public Node {
public:
	Skybox(const std::vector<std::string> &faces, Camera& cam);
	Skybox(const char *prefix, Camera &cam);
	~Skybox();

	void render(RenderContext &c);

	Object *find(int id) override;
private:
	CubeMap* cubemap;
	Model *model;
	Program program;

	void load(const std::vector<std::string> &faces, Camera &camera);
};


