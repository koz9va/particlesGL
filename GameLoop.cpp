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

	PointsAmount = 0;

	for(i = 0; i < MaxLen; ++i) {
		cells[i] = -1;
	}

//	cu::AllocPointsAndCells(wWidth, wHeight, &points_d, &cells_d, points, cells, PointsAmount);

}

GameLoop::~GameLoop() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

//	cu::FreePointsAndCells(points_d, cells_d);

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

	cu::updateSand(points, cells, points_d, cells_d, PointsAmount, wWidth, wHeight, 1);

	while(!quit) {
		while (SDL_PollEvent(&input) > 0) {
			if (input.type == SDL_QUIT) {
				quit = true;
			}
		}

		updatedFrame = 0;

		if((SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))) {
			//std::cout << "x: " << x << " y: " << y << "\n";
			addPoint(x, y);

			updatedFrame = 1;

		}
		if(SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			removePoint(x, y);

			updatedFrame = 1;
		}

//		HSVToRGB((float)i, 100.0f, 100.0f, &rainbow);
//		SDL_SetRenderDrawColor(renderer, rainbow.r, rainbow.g, rainbow.b, 255);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
//		cu::updateSand(points, cells, points_d, cells_d, PointsAmount, wWidth, wHeight, updatedFrame);
		updateSand();
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


//@todo implement resizable sand addition(in circle for example)
//@todo maybe add water
//@todo think about cool shit for portfolio(cuz just sand is boring)
void GameLoop::addPoint(int x, int y) {
	int id;

	if(cells[x + y * wWidth] != -1) {
		return;
	}

	id = PointsAmount++;

	points[id].x = x;
	points[id].y = y;
	points[id].velocity = 0.2;
	points[id].speed = 1.0;

}

void GameLoop::removePoint(int x, int y) {
	int i;
	if(cells[x + y * wWidth] == -1)
		return;

	//points[cells[x + y * wWidth]].isFree = 1;
	if(cells[x + y * wWidth] < PointsAmount - 1) {
		memmove(points + cells[x + y * wWidth], points + cells[x + y * wWidth] + 1,
				sizeof(point_t) * (PointsAmount - cells[x +y *  wWidth] - 1) );
	}

	for(i = 0; i < MaxLen; ++i) {
		cells[i] = -1; //@todo think how to remove shit here and on 158
	}
	--PointsAmount;

	for(i = 0; i < PointsAmount; ++i) { //@todo you can just -1 indexes of left points idiot
		cells[points[i].x + points[i].y * wWidth] = i;
	}
}

void GameLoop::updateSand() {
	int i, j;
	point_t *p;
	bool collided;
	for(j = 0; j < PointsAmount; ++j) {
		collided = false;
		p = points + j;
		for (i = 1; i < (int) ceil(p->speed); ++i) {

			if ((cells[ p->x + (p->y + i) * wWidth] != -1) || (p->y + i) >= wHeight - 3) {
				collided = true;
				break;
			}
		}

		if(i > 1 || (i == 1 && !collided)) {
			--i;
			cells[p->x + p->y * wWidth ] = -1;
			cells[p->x + (p->y + i) * wWidth] = j;
			p->y += i;
			if(!collided && p->speed + p->velocity <= gravity) {
				p->speed += p->velocity;
			} else if(collided)
				p->speed = 1;
			continue;
		}


		collided = false;
		for (i = 1; i < (int) ceil(p->speed); ++i) {
			if ((cells[(p->x + i) + (p->y + i) * wWidth] != -1) || (p->y + i) >= wHeight - 3 || (p->x + i) > wWidth - 3) {
				collided = true;
				break;
			}
		}

		if(i > 1 || (i == 1 && !collided)) {
			--i;
			cells[p->x + p->y * wWidth] = -1;
			cells[(p->x + i) + (p->y + i) * wWidth] = j;
			p->y += i;
			p->x += i;
			if(!collided && p->speed / 2.0 >= 1.0) {
				p->speed /= 1.25;
			} else
				p->speed = 1;
			continue;
		}

		collided = false;
		for (i = 1; i < (int) ceil(p->speed); ++i) {
			if ((cells[(p->x - i) + (p->y + i) * wWidth] != -1) || (p->y + i) >= wHeight - 3 || (p->x - i) < 3) {
				collided = true;
				break;
			}
		}

		if(i > 1 || (i == 1 && !collided)) {
			--i;
			cells[p->x + p->y * wWidth] = -1;
			cells[(p->x + i) + (p->y + i) * wWidth] = j;
			p->y += i;
			p->x -= i;
			if(!collided && p->speed / 2.0 <= 1.0) {
				p->speed /= 1.25;
			} else
				p->speed = 1;
			continue;
		}


	}


}



