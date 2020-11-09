// Created by koz9va on 16.10.20.
//

#ifndef GL_POINT_H
#define GL_POINT_H
#define cos45 0.707106781186
#define gr 0.2
typedef struct point {
	int x;
	int y;
	float velocity; //@todo implement velocity and update sand behavior in general
	float speed;
	
}point_t;
#endif //GL_POINT_H
