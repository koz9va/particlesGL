//
// Created by koz9va on 08.10.20.
//

#include "GameLoop.h"

GameLoop::GameLoop(int wWIDTH, int wHEIGHT, int EXITKEY, int SamplesNum, int RESIZABLE, int POINTSAM, float G)
		:
		wWidth(wWIDTH), wHeight(wHEIGHT), ExitKey(EXITKEY),
		PointsAmount(POINTSAM), gravity(G)
		{
	int i, deb;

	SDL_Init(SDL_INIT_EVERYTHING);
	SandColor.r = 219;
	SandColor.g = 209;
	SandColor.b = 179;
	SandColor.a = 255;
	Cells = new int [wWidth * wHeight];
	Points = new point_t [PointsAmount];


	for(i = 0; i < wWidth * wHeight; ++i) {
		Cells[i] = -1;
	}

	for(i = 0; i < PointsAmount/2; ++i) {
		Points[i].y = wHeight/2 + 10;
		Points[i].x = wWidth/2 + i;
		deb = wWidth/2 + i;
	}
	for(i = PointsAmount/2; i < PointsAmount; ++i) {
		Points[i].y = wHeight/2;
		Points[i].x = wWidth/2 + (PointsAmount - i);
		deb = (PointsAmount - i);
	}


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
//		HSVToRGB((float)i, 100.0f, 100.0f, &rainbow);
//		SDL_SetRenderDrawColor(renderer, rainbow.r, rainbow.g, rainbow.b, 255);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		updateSand();
		renderSand();
		SDL_RenderPresent(renderer);
	}
	std::cout << "Window closed\n";
}

void GameLoop::updateSand() {
	int i;

	for(i = 0; i < PointsAmount; ++i) {
		if(Points[i].y + 2 > wHeight) {
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
void GameLoop::renderSand() {
	int i;

	SDL_SetRenderDrawColor(renderer, SandColor.r, SandColor.g, SandColor.b, SandColor.a);
	MatchPointsToCells(Points, Cells, PointsAmount, wWidth, wHeight);
	for(i = 0; i < PointsAmount; ++i) {
		SDL_RenderDrawPoint(renderer, Points[i].x, Points[i].y);
	}

}




