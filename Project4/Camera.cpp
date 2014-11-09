#include "Camera.h"


Camera::Camera()
{
	
}


Camera::~Camera()
{
}

void Camera::camOut(float move)
{
	eye_z += move;
	update();
}

void Camera::camIn(float move)
{
	eye_z -= move;
	update();
}

void Camera::camUp(float move)
{
	eye_y += move;
	update();
}

void Camera::camDown(float move)
{
	eye_y -= move;
	update();
}

void Camera::camLeft(float move)
{
	eye_x -= move;
	update();
}

void Camera::camRight(float move)
{
	eye_x += move;
	update();
}

void Camera::init()
{
	eye_x = 0;
	eye_y = 2;
	eye_z = 3;

	eye = vmath::vec3(eye_x, eye_y, eye_z);
	center = vmath::vec3(0, 0, 0);
	up = vmath::vec3(0, 1, 0);

	
	//overhead = vmath::rotate((float)60, vmath::vec3(1, 0, 0)) * vmath::rotate((float)-90, vmath::vec3(0, 1, 0));
	view = vmath::lookat(eye, center, up);// *overhead;

	frustum = vmath::frustum(-0.2, 0.2, -0.2, 0.2, 0.3, 100);
}

void Camera::update()
{
	eye = vmath::vec3(eye_x, eye_y, eye_z);
	view = vmath::lookat(eye, center, up);// *overhead;
}

void Camera::reverse()
{
	eye_z = -eye_z;
	eye_x = -eye_x;

	update();
}

// Sets up uniform for the View Projection Matrix
void Camera::render(Shader shader)
{
	glUniformMatrix4fv(shader.getUniformLocation("VPMatrix"), 1, GL_FALSE, frustum * view);
	glUniformMatrix4fv(shader.getUniformLocation("VMatrix"), 1, GL_FALSE, view);
}