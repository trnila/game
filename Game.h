#pragma once
#include <glm/vec4.hpp>
#include "Scene.h"
#include "Singleton.h"
#include "KeyListener.h"
#include "MouseListener.h"
#include "Window.h"

class Game : public Singleton<Game>, public KeyListener, public MouseListener {
public:
	void init();

	void startRendering();

	virtual void onKey(int key, int scancode, int action, int mods) override;

	virtual void onMove(double x, double y) override;
	
protected:
	Game() {};
	friend Singleton<Game>;

private:
	Window *window;
	Scene *scene;
};
