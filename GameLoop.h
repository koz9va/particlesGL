//
// Created by koz9va on 08.10.20.
//

#ifndef GL_GAMELOOP_H
#define GL_GAMELOOP_H

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include "common/helperFuncs.h"
//#include <SDL/SDL.h>



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
private:
	int wWidth;
	int wHeight;
	int ExitKey;
	int PointsAmount;
	int *Cells;
	point_t *Points;
	SDL_Color SandColor;
	SDL_Window *window;
	SDL_Renderer *renderer;
	void updateSand();
	void renderSand();
};


#endif //GL_GAMELOOP_H
