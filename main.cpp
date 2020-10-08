#include "GameLoop.h"


int main(int argc, char* argv[]) {

	if(argc != 3) {
		std::cout << "Wrong number of arguments :(\n";
	}
	GameLoop game(atoi(argv[1]),atoi(argv[2]),
			   GLFW_KEY_ESCAPE, 4, GL_FALSE
			   );
	game.start();

	return 0;
}