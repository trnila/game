#include "Skybox.h"
#include "../Utils/ResourceManager.h"

Skybox::Skybox(const std::vector<std::string> &faces): cubemap() {
	load(faces);
}

void Skybox::load(const std::vector<std::string> &faces) {
	program.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/skybox.v.glsl", GL_VERTEX_SHADER));
	program.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/skybox.f.glsl", GL_FRAGMENT_SHADER));
	program.link();

	program.use();

	cubemap = new CubeMap(faces);
	model = new Model("resources/cube.obj");
}

void Skybox::render(RenderContext &c) {
	program.use();
	GL_CHECK(glDepthMask(GL_FALSE));

	program.useTexture("skybox", *cubemap, 0);
	model->render(c, program);

	GL_CHECK(glDepthMask(GL_TRUE));
}

Skybox::~Skybox() {
	delete model;
	delete cubemap;
}

Skybox::Skybox(const char *prefix) {
	const char suffixes[][3] = {"rt", "lf", "up", "dn", "bk", "ft"};

	std::vector<std::string> faces;
	for(int i = 0; i < sizeof(suffixes) / sizeof(*suffixes); i++) {
		faces.push_back((std::string(prefix) + "_" + suffixes[i] + ".tga").c_str());
	}

	load(faces);
}

Object *Skybox::find(int id) {
	return nullptr;
}
