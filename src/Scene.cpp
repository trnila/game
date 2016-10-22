#include "Scene.h"
#include "data.h"
#include "Logic.h"
#include "Light.h"
GLuint FramebufferName = 0;
GLuint depthTexture;
Program *act;
Window* win;

Scene::Scene(Window &window) : camera(window), camHandler(&camera) {
	initResources();

	createScene();
	win = &window;
}

void Scene::createScene() {
	ResourceManager<Model> &models = ResourceManager<Model>::getInstance();
	ResourceManager<Texture> &textures = ResourceManager<Texture>::getInstance();

	Object *obj;
	Object *terrain = new Object(&models.getResource("resources/terrain_smooth.obj"), prog, nullptr);
//	terrain = new Object(&models.getResource("resources/plane.obj"), prog, nullptr);

	terrain->setPosition(-7, -3, -2);
	terrain->rotate(0, 0, 0, 1);
	terrain->setScale(10, 10, 10);
	terrain->setColor(0, 123 / 255.0f, 10 / 255.0f);

	root.addNode(terrain);

	glm::vec3 center = glm::vec3(0.2787f, 1.811f, -0.48f);

	windMill = new NodeList();
	windMill->move(0, 0.5, 0);

	propeller = new NodeList();
	propeller->move(0, 1, -0.05f);
	propeller->rotate(0, 0.6, 0, 1);
	propeller->attachLogic<RotateLogic>(45);
	// propellers
	glm::vec3 colors[] = {
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1},
			{1, 1, 0}
	};

	obj = new Object(&models.getResource("resources/ball.obj"), prog, nullptr);
	obj->setScale(0.02, 0.02, 0.02);
	obj->setColor(1, 1, 1);
	propeller->addNode(obj);

	for (int i = 0; i < 4; i++) {
		obj = new Object(&models.getResource("redTriangle", triangleVertices, 3), prog, nullptr);
		obj->rotate(90 * i, 0.6, 0, 1);
		obj->setScale(1, 1, 1);
		obj->setColor(colors[i]);
		propeller->addNode(obj);
	}
	// tube
	obj = new Object(&models.getResource("resources/tube.obj"), prog, nullptr);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.05, 1, 0.05);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	windMill->addNode(obj);
	windMill->addNode(propeller);

	root.addNode(windMill);


	NodeList *forest = new NodeList();
	forest->move(17.65, -3.0, 26.88);
	root.addNode(forest);

	obj = new Object(&models.getResource("resources/tree.obj"), prog, nullptr);
	obj->setPosition(4, 0.0f, 0);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.001, 0.001, 0.001);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	obj->attachLogic<TreeLogic>(1.01, 0.1, 5);
	forest->addNode(obj);

	obj = new Object(&models.getResource("resources/tree.obj"), prog, nullptr);
	obj->setPosition(0, 0.0f, 0);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.001, 0.001, 0.001);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	obj->attachLogic<TreeLogic>(1.04, 0.2, 9);
	forest->addNode(obj);


	NodeList *origin = new NodeList;
	root.addNode(origin);
	origin->setPosition(1, 2, 1);
	origin->rotate(90, 0, 0, 1);
	origin->attachLogic<RotateLogic>(45);

	obj = new Object(&models.getResource("redTriangle", triangleVertices, 3), prog, nullptr);
	obj->move(-0.1, -1, 0);
	obj->setColor(1, 0, 0);
	origin->addNode(obj);


	lightNode = new NodeList();
	lightNode->setPosition(-0.280287, 6.302092, -4.222088);
	//lightNode->attachLogic<MoveLogic>();
	root.addNode(lightNode);

	Light *light = new Light(prog);
	light->setDiffuseColor(Color(1, 1, 1));
	light->setSpecularColor(Color(0, 0, 1));
	lightNode->addNode(light);

	/*obj = new Object(&models.getResource("resources/ball.obj"), constantProg, nullptr);
	obj->setColor(1, 0, 0);
	obj->setScale(0.02, 0.02, 0.02);
	lightNode->addNode(obj);*/


	NodeList* cubes = new NodeList();
	cubes->move(10.7, 0.78, 8.81);
	root.addNode(cubes);
	obj = new Object(&models.getResource("resources/cube.obj"), prog, &textures.getResource("resources/wood.png"));
	obj->setPosition(0, 0, 0);
	obj->setColor(1, 0, 0);
	obj->attachLogic<RotateLogic>(40);
	cubes->addNode(obj);

	obj = new Object(&models.getResource("resources/cube.obj"), prog, nullptr);
	obj->setPosition(-2, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, -1, 0, 0);
	obj->attachLogic<RotateLogic>(40);
	cubes->addNode(obj);

	obj = new Object(&models.getResource("resources/monkey.obj"), prog, nullptr);
	obj->setPosition(13, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, 0, -1, 0);
	obj->attachLogic<RotateLogic>(40);
	root.addNode(obj);

	obj = new Object(&models.getResource("resources/monkey_smooth.obj"), prog, nullptr);
	obj->setPosition(10, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, 0, 1, 0);
	obj->attachLogic<RotateLogic>(40);
	root.addNode(obj);

	NodeList *balls = new NodeList();
	balls->move(15, 0, 0);
	root.addNode(balls);

	float coords[][3] = {
			{0, 0, -1},
			{1, 0, 0},
			{0, 0, 1},
			{-1, 0, 0}
	};
	int modif = 2;
	for(int i = 0; i < 4; i++) {
		obj = new Object(&models.getResource("resources/ball.obj"), prog, nullptr);
		obj->setPosition(modif * coords[i][0], modif * coords[i][1], modif * coords[i][2]);
		balls->addNode(obj);
	}


	camera.setPosition(4.119658f, 1.629825f, -4.623707f);
	camera.setRotation(-0.582351f, -0.1290f);

	prog.setAmbientColor(Color(0.05, 0.05, 0.05));
	//prog.setAmbientColor(Color(0, 0, 0));


	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {printf("err\n");}


	act = &prog;
}

void Scene::initResources() {
	try {
		prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.v.glsl", GL_VERTEX_SHADER));
		prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.f.glsl", GL_FRAGMENT_SHADER));
		prog.link();

		shadow.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/shadow.v.glsl", GL_VERTEX_SHADER));
		shadow.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/shadow.f.glsl", GL_FRAGMENT_SHADER));
		shadow.link();

		constantProg.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.v.glsl", GL_VERTEX_SHADER));
		constantProg.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/constant.f.glsl", GL_FRAGMENT_SHADER));
		constantProg.link();

		camera.addListener(&prog);
		camera.addListener(&constantProg);

	} catch(GlslCompileError &err) {
		std::cerr << "GLSL error: " << err.getSource() << " - " << err.what() << "\n";
	}
}

void Scene::update(float time) {
	glm::mat4 parent(1.0f);

	root.update(time, parent);
	windMill->move(0.1 * time, 0, 0);
	camHandler.update(time);
}

glm::mat4 depthViewMatrix = glm::lookAt(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,1,0));
void Scene::renderOneFrame(RenderContext &context) {
	// Compute the MVP matrix from the light's point of view

	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,40);
	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glViewport(0, 0, 1024, 1024);
	shadow.setMatrix("depthMVP", depthMVP);

	context.clearColor(0, 0, 0, 0);
	context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	context.setCamera(&camera);

	context.program = &shadow;
	root.render(context);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, win->getWidth(), win->getHeight());
	context.clearColor(0, 0, 0, 0);
	context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	context.program = act;


	glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
	);
	glm::mat4 depthBiasMVP = biasMatrix*depthMVP;
	prog.setMatrix("depthBias", depthBiasMVP);
	glBindTexture(GL_TEXTURE_2D, depthTexture);

	root.render(context);
}

void Scene::onKey(int key, int scancode, int action, int mods) {
	camHandler.onKey(key, scancode, action, mods);

	if(key == GLFW_KEY_ENTER) {
		lightNode->setPosition(camera.getPosition());
		depthViewMatrix = camera.getTransform();
	}

	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		act = act == &prog ? &shadow : &prog;
	}
}

void Scene::onMove(double x, double y) {
	camHandler.onMove(x, y);
}

