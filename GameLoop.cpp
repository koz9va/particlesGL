//
// Created by koz9va on 08.10.20.
//

#include "GameLoop.h"

GameLoop::GameLoop(int wWIDTH, int wHEIGHT, int EXITKEY, int SamplesNum, int RESIZABLE, int POINTSAM, float G)
		:
		wWidth(wWIDTH), wHeight(wHEIGHT), ExitKey(EXITKEY),
		PointsAmount(POINTSAM), gravity(G)
		{
	SDL_Init(SDL_INIT_EVERYTHING);

	Cells = new int [wWidth * wHeight];
	Points = new point_t [PointsAmount];

}

GameLoop::~GameLoop() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	delete [] Cells;
	delete [] Points;
}

void GameLoop::start() {
	bool quit;
	int i;
	SDL_Color rainbow;
	SDL_Event input;

	quit = false;
	window = SDL_CreateWindow("Sand", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  wWidth, wHeight, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
 	i = 0;
	while(!quit) {
		while (SDL_PollEvent(&input) > 0) {
			if (input.type == SDL_QUIT) {
				quit = true;
			}
		}
		if (++i > 360)
			i = 0;
		HSVToRGB(i, 100, 100, &rainbow);
		SDL_SetRenderDrawColor(renderer, rainbow.r, rainbow.g, rainbow.b, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
	std::cout << "Window closed\n";
}

void GameLoop::updateSand() {
	int i;

	for(i = 0; i < PointsAmount; ++i) {
		if(Points[i].y + 1 > wHeight) {
			Points[i].updatedFrame = false;
			continue;
		}
		if(Cells[wWidth * Points[i].x + (Points[i].y + 1)] < 0) {
			++Points[i].y;
			Points[i].updatedFrame = true;
			continue;
		}
		if(((Points[i].x) < wWidth) &&
		Cells[wWidth * (Points[i].x + 1) + (Points[i].y + 1)] < 0) {
			++Points[i].y;
			++Points[i].x;
			Points[i].updatedFrame = true;
			continue;
		}
		if((Points[i].x > 0) &&
		Cells[wWidth * (Points[i].x - 1) + (Points[i].y + 1)]  < 0) {
			++Points[i].y;
			--Points[i].x;
			Points[i].updatedFrame = true;
			continue;
		}
		Points[i].updatedFrame = false;
		}



	}




