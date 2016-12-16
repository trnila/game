#include "Factory.h"
#include "Graphics/Skybox.h"
#include "Scene.h"
#include "Groups.h"
#include "GeneratedTerrain.h"
#include "Scene/Lights/DirectionalLight.h"

void Factory::fillScene(Scene &scene) {
	std::vector<std::function<void(Scene*)>> groups {
			SkyboxFactory("resources/skyboxes/ely_hills/hills"),
			normal_terrain,
			Forest(),
			TwoCubes(),
			VariousObjects(),
			Earth(),
			Balls(),
			RotatingSpotLight(),
			CombineScanner(),
			create_water,
	        [](Scene* scene) -> void {
		        DirectionalLight *light = scene->getRootNode().createLight<DirectionalLight>(0);
		        light->setDiffuseColor(Color(1, 1, 1));
		        light->setSpecularColor(Color(1, 1, 1));
		        light->setDir(glm::vec3(-0.550664, -0.395870, 0.734885));

		        DirectionalLight *spot = scene->getRootNode().createLight<DirectionalLight>(5);
		        spot->setDiffuseColor(Color(1, 1, 1));
		        spot->setSpecularColor(Color(1, 1, 1));
	        }
	};

	for(auto group: groups) {
		group(&scene);
	}
}
