#include "Game.h"
#include <GLFW/glfw3.h>


int main() {
	Game g;
	g.init();
	g.start();
	
	//glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
