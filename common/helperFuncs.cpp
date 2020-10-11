//
// Created by koz9va on 09.10.20.
//
#include "helperFuncs.h"
#include <cmath>

//void MatchPointsToCells(point_t *points, int *cells, int pointsAmount, int w, int h) {
//	int i;
//	for(i = 0; i < pointsAmount; ++i) {
//		if(points[i].x > w || points[i].y > h)
//			continue;
//
//		cells[w * points[i].x + points[i].y] = i;
//	}
//}
void HSVToRGB(float H, float S, float V, SDL_Color *out) {
	float s, v, C, X, m, r, g, b;
	s = S/100.0f;
	v = V/100.0f;
	C = s * v;
	X = C * (1.0f - fabs(fmod(H/ 60.0f, 2) - 1.0f));
	m = v - C;
	if(H >= 0 && H < 60){
		r = C,g = X,b = 0;
	}
	else if(H >= 60 && H < 120){
		r = X,g = C,b = 0;
	}
	else if(H >= 120 && H < 180){
		r = 0,g = C,b = X;
	}
	else if(H >= 180 && H < 240){
		r = 0,g = X,b = C;
	}
	else if(H >= 240 && H < 300){
		r = X,g = 0,b = C;
	}
	else{
		r = C,g = 0,b = X;
	}
	out->r = (r + m) * 255;
	out->g = (g + m) * 255;
	out->b = (b + m) * 255;
}

