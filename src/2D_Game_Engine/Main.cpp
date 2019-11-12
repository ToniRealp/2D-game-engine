#include "GameContoller.h"
#include <SDL.h>
#undef main

int main() {
	srand(time(NULL));

	GameContoller gameController;
	gameController.Update();

	return 0;
}