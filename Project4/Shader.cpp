#include "Shader.h"


Shader::Shader()
{
}

Shader::~Shader()
{
}

void Shader::init(const char* vert, const char* frag)
{
	// load shader info
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, vert },
		{ GL_FRAGMENT_SHADER, frag },
		{ GL_NONE, NULL },
	};

	// set shader program
	_id = LoadShaders(shaders);
	glUseProgram(_id);
}

void Shader::use()
{
	glUseProgram(_id);
}

void Shader::unuse()
{
	glUseProgram(0);
}

GLint Shader::getUniformLocation(std::string name)
{
	return glGetUniformLocation(_id, name.c_str());
}
