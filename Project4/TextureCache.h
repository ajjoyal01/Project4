


// textures are added cascading down
#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>

#include "Texture.h"

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	void load();
	void saveToFile(std::string filename);
	void add(Texture * texture);
	void activate(GLint uniformLocation);
	void deactivate();


private:
	GLuint _id;

	unsigned int _width;
	unsigned int _height;

	std::vector<unsigned char> _cache;
};

