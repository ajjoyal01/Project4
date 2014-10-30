#include "TextureCache.h"


TextureCache::TextureCache() : 
	_id(0),
	_width(0),
	_height(0)
{
	glGenTextures(1, &_id);
}


TextureCache::~TextureCache()
{
	if (_id != 0)
		glDeleteTextures(1, &_id);
}

void TextureCache::activate(GLint uniformLocation)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _id);
	glUniform1i(uniformLocation, 0);
}

void TextureCache::deactivate()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}



/*
	This only works for images with the same dimensions
	Pre: 
	
*/
void TextureCache::add(Texture * texture)
{
	
	if (_width == 0)
		_width = texture->_width;
	_height += texture->_height;

	_cache.reserve(_cache.size() + texture->_image.size());
	_cache.insert(_cache.end(), texture->_image.begin(), texture->_image.end());

}


void TextureCache::saveToFile(std::string filename)
{
	std::vector<unsigned char> output;
	unsigned error = lodepng::encode(output, _cache, _width, _height);
	if (!error) lodepng::save_file(output, filename);
}


void TextureCache::load()
{
	glBindTexture(GL_TEXTURE_2D, _id);

		glTexImage2D(GL_TEXTURE_2D,
			0,									// level
			GL_RGBA,							// internal format
			_width, _height,					// width, height
			0,									// border
			GL_RGBA, GL_UNSIGNED_BYTE,			// format, type
			&(_cache[0]));						// data

		// Texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
		glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}
