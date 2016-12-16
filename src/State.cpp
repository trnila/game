#include "States.h"
#include "State.h"

void States::add(StateType type, State *state, int key) {
	states[type] = state;
	states[StateType::Normal]->registerTransition(type, key);
}

States::States(Game *game) : game(game) {
	states[StateType::Normal] = new State();
}
