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

	inputType = sand;

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
	Uint32 mouseState;



	quit = false;
	window = SDL_CreateWindow("Sand", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  wWidth, wHeight, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

//	cu::updateSand(points, cells, points_d, cells_d, PointsAmount, wWidth, wHeight, 1);

	while(!quit) {
		while (SDL_PollEvent(&event) > 0) {

			if(event.type == SDL_QUIT) {
				quit = true;
			} else {
				setParticleValue();
			}
		}
		updatedFrame = 0;

		mouseState = SDL_GetMouseState(&x, &y);

		if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			//std::cout << "x: " << x << " y: " << y << "\n";
			addPoint(x, y);

			updatedFrame = 1;

		}
		if(mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			removePoint(x, y);

			updatedFrame = 1;
		}


		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	//	cu::updateSand(points, cells, points_d, cells_d, PointsAmount, wWidth, wHeight, updatedFrame);
		updateSand();
		renderSand();
		SDL_RenderPresent(renderer);
	}
	std::cout << "Window closed\n";
}


void GameLoop::renderSand() {
	int i;
	particleTypes prevColor;


	SDL_SetRenderDrawColor(renderer, SandColor.r, SandColor.g, SandColor.b, SandColor.a);
	prevColor = sand;
	for(i = 0; i < PointsAmount; ++i) {
		if(prevColor != points[i].type) {
			switch (points[i].type) {
				case sand:
					SDL_SetRenderDrawColor(renderer, SandColor.r, SandColor.g, SandColor.b, SandColor.a);
					break;
				case water:
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					break;
				case rock:
					SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255);
			}
		}
		SDL_RenderDrawPoint(renderer, points[i].x, points[i].y);
		prevColor = points[i].type;
	}

}


//@todo implement resizable sand addition(in circle for example)
void GameLoop::addPoint(int x, int y) {
	int id;

	if(cells[x + y * wWidth] != -1) {
		return;
	}

	id = PointsAmount++;

	cells[x + y * wWidth] = id;
	points[id].x = x;
	points[id].y = y;
	points[id].velocity = 0.2;
	points[id].speed = 1.0;
	points[id].type = inputType;

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
		cells[i] = -1;
	}
	--PointsAmount;

	for(i = 0; i < PointsAmount; ++i) { //@todo you can just -1 indexes of left points
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
		if (p->type == sand) {

			for (i = 1; i < (int) ceil(p->speed); ++i) {

				if ((cells[p->x + (p->y + i) * wWidth] != -1) || (p->y + i) >= wHeight - 3) {
					collided = true;
					break;
				}
			}

			if (i > 1 || (i == 1 && !collided)) {
				--i;
				cells[p->x + p->y * wWidth] = -1;
				cells[p->x + (p->y + i) * wWidth] = j;
				p->y += i;
				if (!collided && p->speed + p->velocity <= gravity) {
					p->speed += p->velocity;
				} else if (collided)
					p->speed = 1;
				continue;
			}


			collided = false;
			for (i = 1; i < (int) ceil(p->speed); ++i) {
				if ((cells[(p->x + i) + (p->y + i) * wWidth] != -1) || (p->y + i) >= wHeight - 3 ||
					(p->x + i) > wWidth - 3) {
					collided = true;
					break;
				}
			}

			if (i > 1 || (i == 1 && !collided)) {
				--i;
				cells[p->x + p->y * wWidth] = -1;
				cells[(p->x + i) + (p->y + i) * wWidth] = j;
				p->y += i;
				p->x += i;
				if (!collided && p->speed / 2.0 >= 1.0) {
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

			if (i > 1 || (i == 1 && !collided)) {
				--i;
				cells[p->x + p->y * wWidth] = -1;
				cells[(p->x + i) + (p->y + i) * wWidth] = j;
				p->y += i;
				p->x -= i;
				if (!collided && p->speed / 2.0 <= 1.0) {
					p->speed /= 1.25;
				} else
					p->speed = 1;
				continue;
			}


		}
	}


}

void GameLoop::setParticleValue() {
	if(event.type == SDL_KEYDOWN) {
		switch(event.key.keysym.scancode) {
			case SDL_SCANCODE_S:
				inputType = sand;
				break;
			case SDL_SCANCODE_W:
				inputType = water;
				break;
			case SDL_SCANCODE_R:
				inputType = rock;
				break;
			default:
				break;
		}
	}
}



