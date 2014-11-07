#version 330 core

uniform mat4 VPMatrix;		// view projection matrix

layout(location = 0) in vec4 in_position;
layout(location = 1) in vec2 in_texel;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in int in_textureID;
layout(location = 4) in int	in_isTextured;
layout(location = 5) in int	in_isTransformed;		// if the object is allowed to translate

layout(location = 6) in mat4 ModelMatrix;			// the model translation
layout(location = 10) in vec4 in_color;
layout(location = 11) in mat3 NormalMatrix;

out vec4 vertColor;
out vec3 vertNormal;
out vec2 vertTexCoord;

flat out int textureID;
flat out int vertIsTextured;


void main()
{
	
	if(in_isTransformed == 1)
	{
		gl_Direction = VPMatrix * ModelMatrix * in_position;
		Normal = normalize(NormalMatrix * in_normal);
	}
	else
	{
		gl_Direction = VPMatrix * in_position;
		Normal = in_normal;
	}

	vertColor = in_color;
	vertTexCoord = in_texel;
	vertIsTextured = in_isTextured;
	textureID = in_textureID;
}