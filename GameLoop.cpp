//
// Created by koz9va on 08.10.20.
//

#include "GameLoop.h"

GameLoop::GameLoop(int wWIDTH, int wHEIGHT, int SamplesNum, int RESIZABLE, int POINTSAM, float G)
		:
		wWidth(wWIDTH), wHeight(wHEIGHT),
		PointsAmount(POINTSAM), gravity(G)
		{
	int i;

	SDL_Init(SDL_INIT_EVERYTHING);
	SandColor.r = 219;
	SandColor.g = 209;
	SandColor.b = 179;
	SandColor.a = 255;


	MaxLen = wWidth * wHeight;

	cells = new int [MaxLen];
	points = new point_t [MaxLen];

	cu::AllocPointsAndCells(wWidth, wHeight, &points_d, &cells_d);

	PointsAmount = 0;

	for(i = 0; i < MaxLen; ++i) {
		cells[i] = -1;
	}



}

GameLoop::~GameLoop() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	cu::FreePointsAndCells(points_d, cells_d);

	delete [] cells;
	delete [] points;
}

void GameLoop::start() {
	bool quit;
	int x, y;

	SDL_Event input;

	quit = false;
	window = SDL_CreateWindow("Sand", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  wWidth, wHeight, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);


	while(!quit) {
		while (SDL_PollEvent(&input) > 0) {
			if (input.type == SDL_QUIT) {
				quit = true;
			}

		}
		if((SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))) {
			//std::cout << "x: " << x << " y: " << y << "\n";
			addPoint(x, y);

		}
		if(SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			removePoint(x, y);
		}

//		HSVToRGB((float)i, 100.0f, 100.0f, &rainbow);
//		SDL_SetRenderDrawColor(renderer, rainbow.r, rainbow.g, rainbow.b, 255);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		cu::updateSand(points, cells, points_d, cells_d, PointsAmount, wWidth, wHeight);
		renderSand();
		SDL_RenderPresent(renderer);
	}
	std::cout << "Window closed\n";
}


void GameLoop::renderSand() {
	int i;

	SDL_SetRenderDrawColor(renderer, SandColor.r, SandColor.g, SandColor.b, SandColor.a);

	for(i = 0; i < PointsAmount; ++i) {
		SDL_RenderDrawPoint(renderer, points[i].x, points[i].y);
	}

}



//void GameLoop::MatchPointsToCells() {
//	int i;
//	point_t *iter;
//
//	for(i = 0; i < wWidth * wHeight; ++i) {
//		cells[i] = -1;
//	}
//
//	for(i = 0; i < PointsAmount ++i) {
//
//		if((*iter).x > wWidth || (*iter).y > wHeight)
//			continue;
//		cells[wWidth * (*iter).x + (*iter).y] = iter;
//	}
//}
//@todo implement resizable sand addition(in circle for example)
//@todo maybe add water
//@todo think about cool shit for portfolio(cuz just sand is boring)
void GameLoop::addPoint(int x, int y) {
	int id;
	if(wWidth * x + y >= (wWidth * wHeight)) {//		std::cout << "cursor out of coordinates :(\n";
		return;
	}
	if(cells[wWidth * x + y] != -1) {
		return;
	}


	id = PointsAmount++;

	points[id].x = x;
	points[id].y = y;
	points[id].velocity = gravity;

}

void GameLoop::removePoint(int x, int y) {
	int i;
	if(cells[wWidth * x + y] == -1)
		return;

	//points[cells[wWidth * x + y]].isFree = 1;
	if(cells[wWidth * x + y] < PointsAmount - 1) {
		memmove(points + cells[wWidth * x + y], points + cells[wWidth * x + y] + 1,
				sizeof(point_t) * (PointsAmount - cells[wWidth * x +y] - 1) );
	}

	for(i = 0; i < MaxLen; ++i) {
		cells[i] = -1; //@todo think how to remove shit here and on 158
	}
	--PointsAmount;

	for(i = 0; i < PointsAmount; ++i) {
		cells[wWidth * points[i].x + points[i].y] = i;
	}
}




