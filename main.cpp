#include "Game.h"

int main() {
	Game g;
	g.init();
	g.start();
	
	//glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
