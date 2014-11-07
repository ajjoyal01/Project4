#pragma once

#include "DirectionalLight.h"

#include "vmath.h"



class PointLight : public DirectionalLight
{
public:
	PointLight();
	~PointLight();

	void render(Shader);


private:
	vmath::vec3 _eyeDirection;
	float _constantAttenuation;
	float _linearAttenuation;
	float _quadraticAttenuation;



};

