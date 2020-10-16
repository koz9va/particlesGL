//
// Created by koz9va on 08.10.20.
//

#ifndef GL_GAMELOOP_H
#define GL_GAMELOOP_H

#ifdef __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "common/point.h"
#include "common/SlotMap.h"
#include "common/CUDARuntime/Particles.cuh"
//#include <SDL/SDL.h>




class GameLoop {
public:
	GameLoop(
			int wWIDTH, int wHEIGHT,
		     int SamplesNum,
		    int RESIZABLE, int POINTSAM, float G
		  );
	void start();
	float gravity;
	~GameLoop();
private:
	int wWidth;
	int wHeight;
	int MaxLen;
	//point_t **cells;
	//	std::vector<int64_t> pointsIds;
	//	SlotMap<point_t> points;
	point_t *points;
	int *cells;
	point_t *points_d;
	int *cells_d;
	int PointsAmount;
	SDL_Color SandColor;
	SDL_Window *window;
	SDL_Renderer *renderer;
//	void MatchPointsToCells();
	void renderSand();
	void addPoint(int x, int y);
	void removePoint(int x, int y);
};


#endif //GL_GAMELOOP_H
