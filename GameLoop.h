//
// Created by koz9va on 08.10.20.
//

#ifndef GL_GAMELOOP_H
#define GL_GAMELOOP_H

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include "common/helperFuncs.h"
#include "common/SlotMap.h"
//#include <SDL/SDL.h>

typedef struct point {
	int64_t id;
	int x;
	int y;
	float velocity;
	bool updatedFrame;
}point_t;


class GameLoop {
public:
	GameLoop(
			int wWIDTH, int wHEIGHT,
		    int EXITKEY, int SamplesNum,
		    int RESIZABLE, int POINTSAM, float G
		  );
	void start();
	float gravity;
	~GameLoop();
	const size_t chunk_size = 256;
private:
	int wWidth;
	int wHeight;
	int ExitKey;
	int PointsAmount;
	point_t **cells;
	std::vector<int64_t> pointsIds;
	SlotMap<point_t> points;
	SDL_Color SandColor;
	SDL_Window *window;
	SDL_Renderer *renderer;
	void MatchPointsToCells();
	void updateSand();
	void renderSand();
	void addPoint(int x, int y);
};


#endif //GL_GAMELOOP_H
