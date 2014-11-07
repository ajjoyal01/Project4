#include "PointLight.h"


PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}



void PointLight::render(Shader shader)
{
	DirectionalLight::render(shader);

	glUniform3f(shader.getUniformLocation("EyeDirection"), _eyeDirection[0], _eyeDirection[1], _eyeDirection[2]);
	glUniform1f(shader.getUniformLocation("ConstantAttenuation"), _constantAttenuation);
	glUniform1f(shader.getUniformLocation("LinearAttenuation"), _linearAttenuation);
	glUniform1f(shader.getUniformLocation("QuadraticAttenuation"), _quadraticAttenuation);



}