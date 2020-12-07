// Created by koz9va on 16.10.20.
//

#ifndef GL_POINT_H
#define GL_POINT_H
#define cos45 0.707106781186
#define gr 0.2


enum particleTypes {
	sand,
	rock,
	water
};

typedef struct point {
	int x;
	int y;
	float velocity;
	float speed;
	particleTypes type;
} point_t;
#endif //GL_POINT_H
