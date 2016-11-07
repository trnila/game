#include "States.h"
#include "State.h"

States::States() {
	states[StateType::Normal] = new State();
}

void States::add(StateType type, State *state, int key) {
	states[type] = state;
	states[StateType::Normal]->registerTransition(type, key);
}
