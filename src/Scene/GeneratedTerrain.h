
#pragma once


#include "Terrain.h"

class GeneratedTerrain: public Terrain {
public:
	GeneratedTerrain(Scene &scene);
	
	float getHeightAt(float x, float z);


protected:
	virtual void createTerrain() override;

	float generateHeight(float x, float z) const;
};


