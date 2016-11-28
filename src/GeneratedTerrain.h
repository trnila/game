
#pragma once


#include "Terrain.h"

class GeneratedTerrain: public Terrain {
protected:


public:
	GeneratedTerrain(Mediator &mediator);
	
	float getHeightAt(float x, float z) {
		glm::vec4 pos = glm::inverse(getTransform().getTransform()) * glm::vec4(x, 0, z, 1);
			
		float fScaleC = float(pos.z) / float(getWidth() - 1);
		float fScaleR = float(pos.x) / float(getHeight() - 1);

		glm::vec2 c = glm::vec2(3, 2) * glm::vec2(fScaleC, fScaleR);
		float d =50* (0.5f + 0.5f*glm::perlin(c));

		return (getTransform().getTransform() * glm::vec4(0.0f, d+1, 0.0f, 1.0f)).y;
	}


protected:
	virtual void createTerrain() override;
};


