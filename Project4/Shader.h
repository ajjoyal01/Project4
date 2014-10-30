#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string>
#include "LoadShaders.h"


class Shader
{
public:
	Shader();
	~Shader();

	void init();
	GLint getUniformLocation(std::string);
	void use();
	void unuse();


private:
	GLuint _id;


};

