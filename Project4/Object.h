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
//#include "ObjLoader.h"

using namespace std;

class Object
{

public:

	Object();
	~Object();

	void draw();
	void init(string);
	void loadObject(string);
	void loadObjectTextured(string);

	void scale(float);
	void translate(float, float, float);
	void rotate(float, vmath::vec3);
	void deselect(Shader);
	void select(Shader);
	void updateCenter();
	void calculateDimentions();

	vec4 center;

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

	vmath::mat4 transform;

protected:

	string name;
};

