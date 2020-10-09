//
// Created by koz9va on 09.10.20.
//
#include "helperFuncs.h"

void MatchPointsToCells(point_t *points, int *cells, int pointsAmount, int w, int h) {
	int i;
	for(i = 0; i < pointsAmount; ++i) {
		if(points[i].x > w || points[i].y > h)
			continue;

		cells[w * points[i].x + points[i].y] = i;
	}
}

