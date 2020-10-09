//
// Created by koz9va on 09.10.20.
//

#ifndef GL_HELPERFUNCS_H
#define GL_HELPERFUNCS_H

#include <SDL_quit.h>
#include <SDL_pixels.h>

typedef struct point {
	int x;
	int y;
	float velocity;
	bool updatedFrame;
}point_t;


void MatchPointsToCells(point_t *points, int *cells, int pointsAmount, int w, int h);

void HSVToRGB(float H, float S, float V, SDL_Color *out) ;
#endif //GL_HELPERFUNCS_H
