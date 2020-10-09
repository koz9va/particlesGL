//
// Created by koz9va on 08.10.20.
//

#ifndef GL_GAMELOOP_H
#define GL_GAMELOOP_H

#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "common/Shader.hpp"
#include "common/helperFuncs.h"



class GameLoop {
public:
	GameLoop(
			int wWIDTH, int wHEIGHT,
		    int EXITKEY, int SamplesNum,
		    int RESIZABLE, int POINTSAM, float G
		  );
	void start();
	void updateSand();
	float gravity;
	~GameLoop();
private:
	int wWidth;
	int wHeight;
	int ExitKey;
	int PointsAmount;
	int *Cells;
	point_t *Points;
	GLFWwindow *window;
	GLfloat g_vertex_buffer_data[9];
	GLuint programID;
	GLuint VertexArrayID;
	GLuint vertexbuffer;
};


#endif //GL_GAMELOOP_H
