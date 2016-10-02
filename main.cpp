#include "Game.h"

int main() {
	Game &g = Game::getInstance();
	g.init();
	g.start();
	
	//glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
