#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "vgl.h"
#include "vmath.h"
#include "vec.h"
#include "Shader.h"
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

	void scale(float);
	void translate(float, float, float);
	void rotate(float, vmath::vec3);
	void deselect(Shader);
	void select(Shader);
	void updateCenter();


	vec4 center;

private:

	vector<vmath::vec4> vertices;
	vector<vmath::vec3> normals;
	vector<vmath::vec2> texels;

	//---------------------------------------------------------
	// Declare Data (Vertex Arrays and Buffers)
	//---------------------------------------------------------
	GLuint VAOs[1];
	GLuint Buffers[3];
	//---------------------------------------------------------

	//---------------------------------------------------------
	// Vertex Attributes
	//---------------------------------------------------------
	enum { vPosition, vTexel, vNormal, vIsTextured, vIsTransformed, vModelMatrix};
	//---------------------------------------------------------

	int isTransformed;
	GLuint isTextured;

	vmath::mat4 transform;
	
};

