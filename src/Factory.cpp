#include "Factory.h"
#include "Graphics/Skybox.h"
#include "Scene.h"
#include "Groups.h"
#include "GeneratedTerrain.h"
#include "Scene/Lights/DirectionalLight.h"

void Factory::fillScene(Scene &scene) {
	for(auto group: groups) {
		group(&scene);
	}
}
