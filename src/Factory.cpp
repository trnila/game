#include "Factory.h"
#include "Graphics/Skybox.h"
#include "Scene.h"

void Factory::fillScene(Scene &scene) {
	for(auto group: groups) {
		group(&scene);
	}
}
