#pragma once
#include <unordered_map>
#include "Input/KeyListener.h"
#include "Input/MouseListener.h"


enum class StateType {
	Normal,
	Insert,
	Delete,
	Scale,
	Lights,
	Shoot
};

class State;
class Game;

class States: public KeyListener, public MouseListener {
public:
	States(Game *game);

	void add(StateType type, State *state, int key);

	void change(StateType type) {
		actual = states[type];
	}

	State& current() {
		return *actual;
	}

	void onKey(int key, int scancode, int action, int mods) override;

	void onMove(double x, double y) override;


private:
	std::unordered_map<StateType, State*> states;
	State* actual = nullptr;
	Game *game;
};