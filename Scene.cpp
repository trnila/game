#include "Scene.h"
#include "data.h"

Scene::Scene(GLFWwindow *window) {
	init_resources();

	objects.emplace_back(Object(new Model(triangleVertices, triangleRed, 3)));
	objects.emplace_back(Object(new Model(cubeVertices, cubeRandColors, 36)));
	objects.emplace_back(Object(new Model(triangleVertices, triangleBlue, 3)));

	objects[0].setPosition(-1, 0, -4);
	objects[0].rotate(0, 0, 1, 0);

	objects[1].setPosition(0, 0, -9);
	objects[1].rotate(0, 0, -1, 0);

	objects[2].setPosition(2, 0, -3);
	objects[2].rotate(0, 0, 1, 0);


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));// * glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -8.0));
	projection = glm::perspective(45.0f, 1.0f*width/height, 0.1f, 10.0f);

	// todo: fix!
	mvpVar = prog.bindUniformVariable("mvp");

}

int Scene::init_resources() {
	try {
		Shader vertex = ResourceManager<Shader>::getInstance().getResource<>("triangle.v.glsl", GL_VERTEX_SHADER);
		Shader fragment = ResourceManager<Shader>::getInstance().getResource<>("triangle.f.glsl", GL_FRAGMENT_SHADER);

		prog.attach(vertex);
		prog.attach(fragment);
		prog.link();

	} catch(GlslCompileError &err) {
		std::cerr << "GLSL error: " << err.getSource() << " - " << err.what() << "\n";
	}

	return 1;
}

void Scene::update(float time) {
	float angle = time * 45;

	for(Object &o: objects) {
		o.addAngle(angle);
	}
}

void Scene::renderOneFrame(RenderContext &context) {
	context.clearColor(0, 0, 0, 0);
	context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	context.use(prog);

	for(Object &o: objects) {
		glm::mat4 mvp = projection * view * o.getTransform();
		mvpVar->setData(mvp);
		o.render(context);
	}
}
