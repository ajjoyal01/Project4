#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "vgl.h"
#include "vmath.h"
#include "vec.h"
#include "Shader.h"
#include "Texture.h"
#include "Color.h"
#include "Object.h"

using namespace std;

class Model : public Object
{

public:

	Model();
	~Model();

	void draw(Shader);
	void init(string);
	void loadObject(string);

	void calculateDimentions();
	float getWidth();
	float getHeight();
	float getDepth();

	void activateTextures(Shader);
	void deactivateTextures();

	void setTexture(Texture*, int);

	void scale(float);
	void translate(float, float, float);
	void rotate(float, vmath::vec3);
	void updateCenter();

	void updateTransform(vmath::mat4);

	vec4 center;
	mat4 transform;

private:

	vector<vmath::vec4> vertices;
	vector<vmath::vec2> texels;
	vector<vmath::vec3> normals;
	vector<int> textureIDs;
	vector<Texture*> textures;

	//---------------------------------------------------------
	// Declare Data (Vertex Arrays and Buffers)
	//---------------------------------------------------------
	enum { POS_BUFFER, TEXEL_BUFFER, NORMAL_BUFFER, TEXTURE_BUFFER, NUM_BUFFERS };

	GLuint VAOs[1];
	GLuint Buffers[NUM_BUFFERS];
	//---------------------------------------------------------

	//---------------------------------------------------------
	// Vertex Attributes
	//---------------------------------------------------------
	enum { vPosition, vTexel, vNormal, vTexture, vIsTextured, vIsTransformed, 
		vModelMatrix0, vModelMatrix1, vModelMatrix2, vModelMatrix3, vColor
	};
	//---------------------------------------------------------

	int isTransformed;
	GLuint isTextured;

	Color color;

	float width;
	float height;
	float depth;


protected:

	string name;
};

