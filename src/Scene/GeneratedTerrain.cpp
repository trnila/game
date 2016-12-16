#include <glm/ext.hpp>
#include "GeneratedTerrain.h"

GeneratedTerrain::GeneratedTerrain(Scene &scene) : Terrain(scene) {}

void GeneratedTerrain::createTerrain() {
	createGrid(300, 300);

	for(int j = 0; j < getHeight(); j++) {
		for(int i = 0; i < getWidth(); i++) {
			grid->at(i, j).points = glm::vec3(i, generateHeight(i, j), j);
		}
	}
}

float GeneratedTerrain::generateHeight(float x, float z) const {
	float fScaleC = x / float(getWidth() - 1);
	float fScaleR = z / float(getHeight() - 1);

	glm::vec2 c = glm::vec2(fScaleC, fScaleR) * glm::vec2(3, 2);

	return 0.5f + perlin(c)
	          + 0.5f * perlin(2*c)
	          + 0.25f * perlin(4*c)
	          + 0.13f * perlin(8*c);
}

float GeneratedTerrain::getHeightAt(float x, float z) {
	glm::vec4 pos = glm::inverse(getTransform()) * glm::vec4(x, 0, z, 1);
	float height = generateHeight(pos.x, pos.z);
	return (getTransform() * glm::vec4(0.0f, height, 0.0f, 1.0f)).y;
}
