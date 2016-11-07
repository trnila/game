#pragma once
#include <unordered_map>


enum class StateType {
	Normal,
	Insert,
	Delete,
	Scale,
	Lights,
	Shoot
};

class State;

class States {
public:
	States();
	void add(StateType type, State *state, int key);

	void change(StateType type) {
		actual = states[type];
	}

	State& current() {
		return *actual;
	}

private:
	std::unordered_map<StateType, State*> states;
	State* actual = nullptr;
};