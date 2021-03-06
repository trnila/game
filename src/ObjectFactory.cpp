
#include "ObjectFactory.h"
#include "Utils/ResourceManager.h"

ObjectFactory::ObjectFactory(Program &shader, Program &shadower) : shader(shader), shadower(shadower) {}

Object *ObjectFactory::create(const char *name) {
	ResourceManager<Model> &models = ResourceManager<Model>::getInstance();
	return new Object(++lastId, &models.getResource(name), shader, shadower, nullptr);
}
