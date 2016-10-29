#include <glm/ext.hpp>
#include "Scene.h"
#include "data.h"
#include "Logic.h"
#include "Light.h"
#include "stb_image.h"

GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
};


Scene::Scene(Window &window) : camera(window), camHandler(&camera), window(window) {
	initResources();

	createScene();
}

GLuint textureID;
GLuint skyboxVAO, skyboxVBO;
void Scene::createScene() {
	ResourceManager<Model> &models = ResourceManager<Model>::getInstance();
	ResourceManager<Texture> &textures = ResourceManager<Texture>::getInstance();

	Object *obj;
	Object *terrain = new Object(&models.getResource("resources/terrain_smooth.obj"), prog, shadow, nullptr);
	//terrain = new Object(&models.getResource("resources/plane.obj"), prog, shadow, nullptr);

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

	obj = new Object(&models.getResource("resources/ball.obj"), prog, shadow, nullptr);
	obj->setScale(0.02, 0.02, 0.02);
	obj->setColor(1, 1, 1);
	propeller->addNode(obj);

	for (int i = 0; i < 4; i++) {
		obj = new Object(&models.getResource("redTriangle", triangleVertices, 3), prog, shadow, nullptr);
		obj->rotate(90 * i, 0.6, 0, 1);
		obj->setScale(1, 1, 1);
		obj->setColor(colors[i]);
		propeller->addNode(obj);
	}
	// tube
	obj = new Object(&models.getResource("resources/tube.obj"), prog, shadow, nullptr);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.05, 1, 0.05);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	windMill->addNode(obj);
	windMill->addNode(propeller);

	root.addNode(windMill);


	NodeList *forest = new NodeList();
	forest->move(17.65, -3.0, 26.88);
	root.addNode(forest);

	obj = new Object(&models.getResource("resources/tree.obj"), prog, shadow, nullptr);
	obj->setPosition(4, 0.0f, 0);
	obj->rotate(0, 0, 0, 1);
	obj->setScale(0.001, 0.001, 0.001);
	obj->setColor(139 / 255.0f, 69 / 255.0f, 19 / 255.0f);
	obj->attachLogic<TreeLogic>(1.01, 0.1, 5);
	forest->addNode(obj);

	obj = new Object(&models.getResource("resources/tree.obj"), prog, shadow, nullptr);
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

	obj = new Object(&models.getResource("redTriangle", triangleVertices, 3), prog, shadow, nullptr);
	obj->move(-0.1, -1, 0);
	obj->setColor(1, 0, 0);
	origin->addNode(obj);


	lightContainer = new NodeList();
	lightContainer->setPosition(15.514797f, 2.126692f, 0.289154f);
	lightContainer->rotate(0, 0, 1, 0);
	lightContainer->attachLogic<RotateLogic>(45);
	root.addNode(lightContainer);

	lightNode = new Light(prog);
	lightNode->setPosition(10, 10, 10);
	lightNode->setDiffuseColor(Color(1, 1, 1));
	lightNode->setSpecularColor(Color(0, 0, 1));
	lightNode->setDirection(glm::vec3(15.514797f, 2.126692f, 0.289154f));
	lightContainer->addNode(lightNode);
	//root.addNode(lightNode);

	/*obj = new Object(&models.getResource("resources/ball.obj"), prog, shadow, nullptr);
	obj->move(12, 10, 10);
	obj->setColor(1, 0, 0);
	lightContainer->addNode(obj);*/


	NodeList* cubes = new NodeList();
	cubes->move(10.7, 0.78, 8.81);
	root.addNode(cubes);
	obj = new Object(&models.getResource("resources/cube.obj"), prog, shadow,
	                 &textures.getResource("resources/cube.png"));
	obj->setPosition(0, 0, 0);
	obj->setColor(1, 0, 0);
	obj->attachLogic<RotateLogic>(40);
	cubes->addNode(obj);

	obj = new Object(&models.getResource("resources/cube.obj"), prog, shadow,
	                 &textures.getResource("resources/cube_wood.png"));
	obj->setPosition(-2, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, -1, 0, 0);
	obj->attachLogic<RotateLogic>(40);
	cubes->addNode(obj);

	obj = new Object(&models.getResource("resources/monkey.obj"), prog, shadow, nullptr);
	obj->setPosition(13, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, 0, -1, 0);
	obj->attachLogic<RotateLogic>(40);
	root.addNode(obj);

	obj = new Object(&models.getResource("resources/monkey_smooth.obj"), prog, shadow, nullptr);
	obj->setPosition(10, 0, 3);
	obj->setColor(1, 0, 0);
	obj->rotate(0, 0, 1, 0);
	obj->attachLogic<RotateLogic>(40);
	root.addNode(obj);

	obj = new Object(&models.getResource("resources/Vortigaunt/vortigaunt.obj"), prog, shadow, &textures.getResource("resources/Vortigaunt/Texture/vortigaunt_sheet.tga"));
	obj->setColor(1, 1, 1);
	obj->setPosition(15, 0, 5);
	obj->setScale(1.f);
	obj->setScale(0.01);
	root.addNode(obj);

	obj = new Object(&models.getResource("resources/D0G/a.obj"), prog, shadow, &textures.getResource("resources/D0G/Texture/dog_sheet.tga"));
	obj->setColor(1, 1, 1);
	obj->setPosition(16, 0, 5);
	obj->setScale(1.f);
	root.addNode(obj);

	obj = new Object(&models.getResource("resources/Headcrab classic/headcrabclassic.obj"), prog, shadow, &textures.getResource("resources/Headcrab classic/Texture/headcrabsheet.tga"));
	obj->setColor(1, 1, 1);
	obj->setPosition(18, 0, 5);
	obj->setScale(0.05f);
	root.addNode(obj);

	obj = new Object(&models.getResource("resources/Strider/Strider.obj"), prog, shadow, &textures.getResource("resources/Strider/Texture/striderdecalsheet.tga"));
	obj->setColor(1, 1, 1);
	obj->setPosition(18, -5, 30);
	obj->setScale(0.02f);
	root.addNode(obj);

	//obj = new Object(&models.getResource("resources/Strider/Strider.obj"), prog, shadow, nullptr);
	//obj = new Object(&models.getResource("resources/Gman/gman.obj"), prog, shadow, nullptr);
	//obj = new Object(&models.getResource("resources/AntLion/AntLion.obj"), prog, shadow, nullptr);
	obj = new Object(&models.getResource("resources/Combine Scanner/Combine_Scanner.obj"), prog, shadow, &textures.getResource("resources/Combine Scanner/Texture/scanner_sheet.tga"));
	obj->setColor(1, 1, 1);
	obj->setPosition(18, 0, 5);
	obj->setScale(0.01f);
	obj->attachLogic<FollowLogic>(&camera);
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
		obj = new Object(&models.getResource("resources/ball.obj"), prog, shadow, nullptr);
		obj->setPosition(modif * coords[i][0], modif * coords[i][1], modif * coords[i][2]);
		balls->addNode(obj);
	}


	camera.setPosition(4.119658f, 1.629825f, -4.623707f);
	camera.setRotation(-0.582351f, -0.1290f);

	prog.setAmbientColor(Color(0.05, 0.05, 0.05));
	//prog.setAmbientColor(Color(0, 0, 0));


	skyboxProg.use();
	GL_CHECK(glGenTextures(1, &textureID));
	GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, textureID));

	std::vector<const GLchar*> faces;
	faces.push_back("resources/skyboxes/ely_hills/hills_rt.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_lf.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_up.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_dn.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_bk.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_ft.tga");


	int width,height;
	unsigned char* image;
	for(GLuint i = 0; i < faces.size(); i++)
	{
		int x,y,n;
		image = stbi_load(faces[i], &width, &height, &n, 3);
		if(!image) {
			throw std::runtime_error("ff");
		}
		GL_CHECK(glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
		));
	}

	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));


	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);
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

		skyboxProg.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/skybox.v.glsl", GL_VERTEX_SHADER));
		skyboxProg.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/skybox.f.glsl", GL_FRAGMENT_SHADER));
		skyboxProg.link();

		camera.addListener(&prog);
		camera.addListener(&constantProg);
		camera.addListener(&skyboxProg);

		depthBuffer = new FrameBuffer(1920, 1080, GL_DEPTH_COMPONENT16);

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

void Scene::renderOneFrame(RenderContext &context) {
	context.setStage(RenderStage::Shadow);

	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 200);
	glm::mat4 depthViewMatrix = glm::lookAt(lightNode->getWorldPosition(), lightNode->getDirection(), glm::vec3(0,1,0));
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix;

	{
		auto buffer = depthBuffer->activate();

		shadow.setMatrix("depthMVP", depthMVP);

		context.clearColor(0, 0, 0, 0);
		context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		context.setCamera(&camera);

		shadow.use();
		root.render(context);
	}

	context.setStage(RenderStage::Normal);
	window.setViewport();
	context.clearColor(0, 0, 0, 0);
	context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skyboxProg.use();
	GL_CHECK(glDepthMask(GL_FALSE));
	//TODO: ... Set view and projection matrix
	glm::mat4 view = glm::mat4(glm::mat3(camera.getTransform()));
	skyboxProg.setMatrix("viewMatrix", view);
	skyboxProg.setMatrix("projectionMatrix", camera.getPerspective());

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(skyboxProg.id, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 36));
	GL_CHECK(glDepthMask(GL_TRUE));

	glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
	);
	glm::mat4 depthBiasMVP = biasMatrix*depthMVP;
	prog.setMatrix("depthBias", depthBiasMVP);

	prog.useTexture("shadowTexture", depthBuffer->getTexture(), 1);
	root.render(context);
}

void Scene::onKey(int key, int scancode, int action, int mods) {
	camHandler.onKey(key, scancode, action, mods);

	if(key == GLFW_KEY_ENTER) {
		//lightNode->setPosition(camera.getPosition());
		//lightNode->setDirection(camera.getDirection());
	}
}

void Scene::onMove(double x, double y) {
	camHandler.onMove(x, y);
}

