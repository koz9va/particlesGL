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

class GameLoop {
public:
	GameLoop(int wWIDTH, int wHEIGHT, int EXITKEY, int SamplesNum, int RESIZABLE);
	void start();

private:
	int wWidth;
	int wHeight;
	int ExitKey;
	GLFWwindow *window;
	GLfloat g_vertex_buffer_data[9];
	GLuint programID;
	GLuint VertexArrayID;
	GLuint vertexbuffer;
};



#endif //GL_GAMELOOP_H
