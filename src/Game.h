#pragma once
#include <glm/vec4.hpp>
#include "Scene.h"
#include "Utils/Singleton.h"
#include "Input/KeyListener.h"
#include "Input/MouseListener.h"
#include "Window.h"
class States;

class Game : public Singleton<Game>, public KeyListener, public MouseListener {
public:
	void init();

	void startRendering();

	virtual void onKey(int key, int scancode, int action, int mods) override;
	virtual void onMove(double x, double y) override;
	virtual void onClick(int button, int action, double x, double y);


	Window &getWindow();

	void addMouse(MouseListener* m) {
		mouse.push_back(m);
	}

	void addKeyboard(KeyListener* key) {
		keyboard.push_back(key);
	}

	States *getStates();

	Scene *getScene();

protected:
	Game() {};
	friend Singleton<Game>;

private:
	Window *window;
	Scene *scene;
	std::vector<MouseListener*> mouse;
	std::vector<KeyListener*> keyboard;
	States *states;
};
