#include "Skybox.h"
#include "ResourceManager.h"

Skybox::Skybox(): cubemap() {
	program.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/skybox.v.glsl", GL_VERTEX_SHADER));
	program.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/skybox.f.glsl", GL_FRAGMENT_SHADER));
	program.link();

	program.use();

	std::vector<const char*> faces;
	faces.push_back("resources/skyboxes/ely_hills/hills_rt.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_lf.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_up.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_dn.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_bk.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_ft.tga");

	cubemap = new CubeMap(faces);
	model = new Model("resources/cube.obj");
}

void Skybox::render(Camera camera) {
	program.use();
	GL_CHECK(glDepthMask(GL_FALSE));

	glm::mat4 view = glm::mat4(glm::mat3(camera.getTransform()));
	program.setMatrix("viewMatrix", view);
	program.setMatrix("projectionMatrix", camera.getPerspective());

	program.useTexture("skybox", *cubemap, 0);
	RenderContext c;
	model->render(c, program);

	GL_CHECK(glDepthMask(GL_TRUE));
}

Skybox::~Skybox() {
	delete model;
	delete cubemap;
}
