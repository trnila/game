#pragma once
#include <glm/vec4.hpp>
#include "Scene.h"
#include "Utils/Singleton.h"
#include "Input/KeyListener.h"
#include "Input/MouseListener.h"
#include "Window.h"

class Game : public Singleton<Game>, public KeyListener, public MouseListener {
public:
	void init();

	void startRendering();

	virtual void onKey(int key, int scancode, int action, int mods) override;
	virtual void onMove(double x, double y) override;
	virtual void onClick(int button, int action, double x, double y) {
		scene->onClick(button, action, x, y);
	}

	
protected:
	Game() {};
	friend Singleton<Game>;

private:
	Window *window;
	Scene *scene;
};
