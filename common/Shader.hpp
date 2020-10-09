//
// Created by koz9va on 08.10.20.
//

#ifndef GL_SHADER_HPP
#define GL_SHADER_HPP

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

#endif //GL_SHADER_HPP
