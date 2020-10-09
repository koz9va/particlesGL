//
// Created by koz9va on 09.10.20.
//

#ifndef GL_HELPERFUNCS_H
#define GL_HELPERFUNCS_H

typedef struct point {
	int x;
	int y;
	float velocity;
	bool updatedFrame;
}point_t;


void MatchPointsToCells(point_t *points, int *cells);

#endif //GL_HELPERFUNCS_H
