#include "Game.h"

int main() {
	Game &g = Game::getInstance();
	g.init();
	g.startRendering();
	
	//glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
