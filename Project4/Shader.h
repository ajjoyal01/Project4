#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string>
#include "LoadShaders.h"

using namespace std;

class Shader
{
public:
	Shader();
	~Shader();

	void init();
	void init(const char*, const char*);
	GLint getUniformLocation(std::string);
	void use();
	void unuse();


private:
	GLuint _id;


};

