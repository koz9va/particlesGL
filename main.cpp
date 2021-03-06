#include "GameLoop.h"

int main(int argc, char *argv[]) {

	if (argc != 3) {
		std::cout << "Wrong number of arguments :(\n";
		return -1;
	}
	GameLoop game(
			atoi(argv[1]),
			atoi(argv[2]),
			 4,
			  0,
			  10,
			  9.8f
	);

	game.start();

	return 0;
}