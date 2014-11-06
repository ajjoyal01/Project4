#version 330 core

out vec4 fragColor;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

uniform vec3 Ambient;
uniform vec3 LightColor;
uniform vec3 LightDirection;
uniform vec3 HalfVector; // surface orientation for shiniest spot
uniform float Shininess;
uniform float Strength;
uniform float directionalLightingOn;

flat in int textureID;
in vec4 vertColor;
in vec3 Normal;
in vec2 vertTexCoord;
flat in int vertIsTextured;


void main()
{
	// to see how much light would be reflected
	float diffuse = max(0.0, dot(Normal, LightDirection));
	float specular = max(0.0, dot(Normal, HalfVector));

	// surfaces facing away from the light (negative dot products)
	// wont be lit by the directional light
	if (diffuse == 0.0)
		specular = 0.0;
	else
		specular = pow(specular, Shininess); // sharpen the highlight
	vec3 scatteredLight = Ambient + LightColor * diffuse;
	vec3 reflectedLight = LightColor * specular * Strength;

	// dont modulate the underlying color with reflected light,
	// only with scattered light
	vec3 rgb = min(vertColor.rgb * scatteredLight + reflectedLight, vec3(1.0));

	if(directionalLightingOn == 1) {
		if(vertIsTextured == 1)
		{

			switch(textureID)
			{
			case 0:
				rgb = min(texture(tex0, vertTexCoord).rgb * scatteredLight + reflectedLight, vec3(1.0));
				fragColor = vec4(rgb, texture(tex0, vertTexCoord).a);
				break;
			case 1:
				rgb = min(texture(tex1, vertTexCoord).rgb * scatteredLight + reflectedLight, vec3(1.0));
				fragColor = vec4(rgb, texture(tex1, vertTexCoord).a);
				break;
			case 2:
				rgb = min(texture(tex2, vertTexCoord).rgb * scatteredLight + reflectedLight, vec3(1.0));
				fragColor = vec4(rgb, texture(tex2, vertTexCoord).a);
				break;
			}
				
		}
		else 
		{
			rgb = min(vertColor.rgb * scatteredLight + reflectedLight, vec3(1.0));
			fragColor = vec4(rgb, vertColor.a);
		}
	} else 
		if(vertIsTextured == 1)
		{
			switch(textureID)
			{
			case 0:
				fragColor = texture(tex0, vertTexCoord);
				break;
			case 1:
				fragColor = texture(tex1, vertTexCoord);
				break;
			case 2:
				fragColor = texture(tex2, vertTexCoord);
				break;
			}
		}
		else 
			fragColor = vertColor;



}