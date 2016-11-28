
#include <glm/ext.hpp>
#include "GeneratedTerrain.h"

void GeneratedTerrain::createTerrain() {
	createGrid(300, 300);

	float fTextureU = float(getWidth()) * 0.1f;
	float fTextureV = float(getHeight()) * 0.1f;

	for(int j = 0; j < getHeight(); j++) {
		for(int i = 0; i < getWidth(); i++) {
			Data &point = grid[i][j];

			float fScaleC = float(j)/float(getWidth() - 1);
			float fScaleR = float(i)/float(getHeight() - 1);

			glm::vec2 c = glm::vec2(3, 2) * glm::vec2(fScaleC, fScaleR);
			const float d = 0.5f + 0.5f*glm::perlin(c);

			point.points = glm::vec3(i , 50*d, j);

			point.uvcoord = glm::vec2(fTextureU * fScaleC, fTextureV * fScaleR);
		}
	}
}

GeneratedTerrain::GeneratedTerrain(Mediator &mediator) : Terrain(mediator) {}
