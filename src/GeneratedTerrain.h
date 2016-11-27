
#pragma once


#include "Terrain.h"

class GeneratedTerrain: public Terrain {
protected:


public:
	GeneratedTerrain(Mediator &mediator);

protected:
	virtual void createTerrain() override;
};


