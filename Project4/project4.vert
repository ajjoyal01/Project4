#version 330 core

uniform mat4 VPMatrix;		// view projection matrix

layout(location = 0) in	vec4 in_position;
layout(location = 1) in vec2 in_texel;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in int	in_isTextured;
layout(location = 4) in int	in_isTransformed;		// if the object is allowed to translate
layout(location = 5) in mat4 ModelMatrix;			// the model translation
layout(location = 9) in vec4 in_color;
layout(location = 10)in mat3 NormalMatrix;

out vec4 vertColor;
out vec2 vertTexCoord;
flat out int vertIsTextured;

out vec3 Normal;

void main()
{
	
	if(in_isTransformed == 1)
	{
		gl_Position = VPMatrix * ModelMatrix * in_position;
	}
	else
	{
		gl_Position = VPMatrix * in_position;
	}

	vertColor = vec4(.6,.4,.1,1);
	vertTexCoord = in_texel;
	vertIsTextured = in_isTextured;
	//Normal = normalize(NormalMatrix * inNormal);
	Normal = in_normal;
}