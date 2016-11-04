#include "Game.h"
#include "Utils/StreamLog.h"
#include <assimp/DefaultLogger.hpp>

int main() {
	Assimp::Logger *logger = Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
	logger->attachStream(new StreamLog(std::cerr), Assimp::Logger::Debugging);

	Game &g = Game::getInstance();
	g.init();
	g.startRendering();
	
	//glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
