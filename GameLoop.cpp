//
// Created by koz9va on 08.10.20.
//

#include "GameLoop.h"



GameLoop::GameLoop(int wWIDTH, int wHEIGHT, int EXITKEY, int SamplesNum, int RESIZABLE, int POINTSAM, float G)
		:
		wWidth(wWIDTH), wHeight(wHEIGHT), ExitKey(EXITKEY),
		PointsAmount(POINTSAM), gravity(G)
		{
	g_vertex_buffer_data[0] = -1.0f;
	g_vertex_buffer_data[1] = -1.0f;
	g_vertex_buffer_data[2] = 0.0f;
	g_vertex_buffer_data[3] = 1.0f;
	g_vertex_buffer_data[4] = -1.0f;
	g_vertex_buffer_data[5] = 0.0f;
	g_vertex_buffer_data[6] = 0.0f;
	g_vertex_buffer_data[7] = 1.0f;
	g_vertex_buffer_data[8] = 0.0f;
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW :(\n";
		exit(-1);
	}


	glfwWindowHint(GLFW_SAMPLES, SamplesNum);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, RESIZABLE);


	window = glfwCreateWindow(wWidth, wHeight, "Particles", nullptr, nullptr);

	if (!window) {
		std::cout << "Failed to open GLFW window. :(\n";
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "failed to init GLEW :(\n";
		glfwTerminate();
		exit(-1);
	}

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	programID = LoadShaders("../shaders/SimpleVertexShader.glsl",
							"../shaders/SimpleFragmentShader.glsl"
	);
	Cells = new int [wWidth * wHeight];
	Points = new point_t [PointsAmount];
}

GameLoop::~GameLoop() {
	delete [] Cells;
	delete [] Points;
}

void GameLoop::start() {

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
				0,
				3,       //size
				GL_FLOAT,   //type
				GL_FALSE,   //normalize?
				0,       // stride
				(void *) nullptr  //array buffer offset
		);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, ExitKey) != GLFW_PRESS &&
			 glfwWindowShouldClose(window) == 0);

	std::cout << "Window closed\n";
}

void GameLoop::updateSand() {
	int i;

	for(i = 0; i < PointsAmount; ++i) {
		if(Points[i].y + 1 > wHeight) {
			Points[i].updatedFrame = false;
			continue;
		}
		if(Cells[wWidth * Points[i].x + (Points[i].y + 1)] < 0) {
			++Points[i].y;
			Points[i].updatedFrame = true;
			continue;
		}
		if(((Points[i].x) < wWidth) &&
		Cells[wWidth * (Points[i].x + 1) + (Points[i].y + 1)] < 0) {
			++Points[i].y;
			++Points[i].x;
			Points[i].updatedFrame = true;
			continue;
		}
		if((Points[i].x > 0) &&
		Cells[wWidth * (Points[i].x - 1) + (Points[i].y + 1)]  < 0) {
			++Points[i].y;
			--Points[i].x;
			Points[i].updatedFrame = true;
			continue;
		}
		Points[i].updatedFrame = false;
		}



	}




