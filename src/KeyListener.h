#pragma once

class KeyListener {
public:
	virtual void onKey(int key, int scancode, int action, int mods) = 0;
};