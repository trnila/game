#include "Groups.h"

void CameraFactory::operator()(Scene *scene) {
		Camera *camera = new Camera(game->getWindow());
		CameraHandler *handler = new CameraHandler(camera);
		camera->attachLogic([=](Node &node, float df, Scene &root) -> void {
			handler->operator()(node, df, root);
		});
		game->addMouse(handler);
		game->addKeyboard(handler);

		std::vector<glm::vec3> points{
				glm::vec3{169.405823, 29.026913, 229.200348},
				glm::vec3{30.499992, 45.105583, 389.684570},
				glm::vec3{100.498253, 35.516335, 972.503296},
				glm::vec3{476.771637, 38.537769, 994.582825},
				glm::vec3{771.374695, 139.720657, 853.438232},
				glm::vec3{637.488220, 90.142654, 698.663940},
				glm::vec3{1196.538574, -30.870426, 604.598755},
				glm::vec3{1197.368164, -30.758410, 605.162354},
				glm::vec3{1116.818970, 57.950874, 135.645493},
				glm::vec3{840.971680, 74.526375, 377.371704},
				glm::vec3{169.405823, 29.026913, 229.200348},
		};
		camera->attachLogic("showcase", Bezier(points, 1, [](Node &node) -> void {
			node.removeLogic("showcase");
			node.setPosition(188.013016f, 100 + 33.348019f, 208.685776f);
			node.attachLogic(CamInit());
		}));
		camera->setZFar(20000);
		scene->getRootNode().addNode(camera);
		scene->setActiveCamera(camera);
	}

void create_water(Scene *scene) {
	Program *water = new Program();
	water->attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/model.v.glsl", GL_VERTEX_SHADER));
	water->attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/water.f.glsl", GL_FRAGMENT_SHADER));
	water->link();
	scene->getActiveCamera().addListener(water);

	ResourceManager<Model> &models = ResourceManager<Model>::getInstance();
	Object *obj = new Object(0, &models.getResource("resources/brickwall.obj"), *water, *water, nullptr);
	obj->setScale(1000);
	obj->setPosition(100, -150, 0);
	scene->getRootNode().addNode(obj);
}

void normal_terrain(Scene *scene) {
	Terrain* terrain = new GeneratedTerrain(*scene);
	terrain->init();
	terrain->setScale(5, 90, 5);
	scene->getRootNode().addNode(terrain);
}
