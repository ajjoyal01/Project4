#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>
#include <math.h>

#include "LoadShaders.h"
#include "vgl.h"
#include "vmath.h"

#include "Shader.h"

using vmath::mat4;

class Camera
{
public:
	Camera();
	~Camera();

	void camOut(float);
	void camIn(float);
	void camUp(float);
	void camDown(float);
	void camLeft(float);
	void camRight(float);
	void init();
	void update();
	void reverse();
	void render(Shader);

private:

	float eye_x;
	float eye_y;
	float eye_z;

	vmath::vec3 center;
	vmath::vec3 up;
	vmath::vec3 eye;

	mat4 view;
	mat4 frustum;
	mat4 overhead;
};

