/*
	DirectonalLight.h
	Author: Gregory Venezia
	Date: 10/27/2014
	Course: CSC5210
	Description: A light pointing an a particular direction
*/


#pragma once

#include "Shader.h"
#include "Color.h"

#include "vmath.h"

class DirectionalLight
{
public:
	DirectionalLight();
	~DirectionalLight();

	void render(Shader shader);
	void init();

	void setAmbient(Color color);
	void setColor(Color color);
	void setNormalMatrix(vmath::matNM<float, 3, 3> matrix);
	void setDirection(vmath::vec3);
	void setStrength(float strength);
	void setShininess(float shininess);
	void toggle();

	// Translations
	void translate(float x, float y, float z);


private:

	Color _ambient;
	vmath::matNM<float, 3, 3> _normalMatrix;
	Color _color; // determines the color of the light
	vmath::vec3 _direction;
	vmath::vec3 _halfVector; // not sure what this does
	float _shininess;
	float _strength;
	bool _on;




};

