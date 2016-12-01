
#pragma once


#include "Terrain.h"

class GeneratedTerrain: public Terrain {
protected:


public:
	GeneratedTerrain(Mediator &mediator);
	
	float getHeightAt(float x, float z);


protected:
	virtual void createTerrain() override;

	float generateHeight(float x, float z) const;
};


