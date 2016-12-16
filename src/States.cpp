#include "States.h"
#include "State.h"

void States::onKey(int key, int scancode, int action, int mods) {
	current().onKey(key, scancode, action, mods, game);
}

void States::onMove(double x, double y) {

}

