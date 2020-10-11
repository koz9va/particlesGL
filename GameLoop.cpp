//
// Created by koz9va on 08.10.20.
//

#include "GameLoop.h"

GameLoop::GameLoop(int wWIDTH, int wHEIGHT, int EXITKEY, int SamplesNum, int RESIZABLE, int POINTSAM, float G)
		:
		wWidth(wWIDTH), wHeight(wHEIGHT), ExitKey(EXITKEY),
		PointsAmount(POINTSAM), gravity(G)
		{
	int i;

	SDL_Init(SDL_INIT_EVERYTHING);
	SandColor.r = 219;
	SandColor.g = 209;
	SandColor.b = 179;
	SandColor.a = 255;
	cells = new point_t *[wWidth * wHeight];
	memset(cells, 0, wWidth * wHeight *sizeof(point_t*));

	pointsIds.reserve(2048);



}

GameLoop::~GameLoop() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	delete [] cells;
}

void GameLoop::start() {
	bool quit;
	int i, x, y, px, py;
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
		if((SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))) {
			//std::cout << "x: " << x << " y: " << y << "\n";
			addPoint(x, y);

		}
		if(SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			removePoint(x, y);
		}
//		if (++i > 360)
//			i = 0;
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
	point_t *iter;
	for(i = 0; i < pointsIds.size(); ++i) {
		iter = points.get_object(pointsIds[i]);
		if(!iter) {
			pointsIds.erase(pointsIds.begin() + i);
			continue;
		}
		if((*iter).y + 2 > wHeight) {
			(*iter).updatedFrame = false;
			continue;
		}
		if(cells[wWidth * (*iter).x + ((*iter).y + 1)] == nullptr) {
			++(*iter).y;
			(*iter).updatedFrame = true;
			continue;
		}
		if((((*iter).x) < wWidth) &&
		cells[wWidth * ((*iter).x + 1) + ((*iter).y + 1)] == nullptr) {
			++(*iter).y;
			++(*iter).x;
			(*iter).updatedFrame = true;
			continue;
		}
		if(((*iter).x > 0) &&
		cells[wWidth * ((*iter).x - 1) + ((*iter).y + 1)] == nullptr) {
			++(*iter).y;
			--(*iter).x;
			(*iter).updatedFrame = true;
			continue;
		}
		(*iter).updatedFrame = false;
		}

	}
void GameLoop::renderSand() {
	int i;
	point_t *iter;
	SDL_SetRenderDrawColor(renderer, SandColor.r, SandColor.g, SandColor.b, SandColor.a);
	MatchPointsToCells();
	for(i = 0; i < pointsIds.size(); ++i) {
		iter = points.get_object(pointsIds[i]);
		SDL_RenderDrawPoint(renderer, (*iter).x, (*iter).y);
	}

}

void GameLoop::MatchPointsToCells() {
	int i;
	point_t *iter;
	memset(cells, 0, wWidth * wHeight * sizeof(point_t*));
	for(i = 0; i < pointsIds.size(); ++i) {
		iter = points.get_object(pointsIds[i]);
		if(!iter) {
			pointsIds.erase(pointsIds.begin() + i);
			continue;
		}
		if((*iter).x > wWidth || (*iter).y > wHeight)
			continue;
		cells[wWidth * (*iter).x + (*iter).y] = iter;
	}
}
//@todo implement resizable sand addition(in circle for example)
//@todo maybe add water
//@todo think about cool shit for portfolio(cuz just sand is boring)
void GameLoop::addPoint(int x, int y) {
	point_t *point;
	if(wWidth * x + y >= (wWidth * wHeight)) {
//		std::cout << "cursor out of coordinates :(\n";
		return;
	}
	if(cells[wWidth * x + y] != nullptr) {
		return;
	}
	pointsIds.push_back(points.create_object());
	point = points.get_object(pointsIds.back());
	point->x = x;
	point->y = y;
}

void GameLoop::removePoint(int x, int y) {
	if(cells[wWidth * x + y] == nullptr)
		return;
	points.destroy_object((*cells[wWidth * x + y]).id);

}



