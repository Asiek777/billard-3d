#version 330 core
out vec4 FragColor;
in vec3 Color;
in vec4 deep;
uniform bool isFog;
uniform vec3 FogColor;

void main()
{			
	if(isFog)		
		FragColor = vec4(mix(Color, FogColor, max(min(-deep.z/deep.w/20, 1.0), 0.0)), 1.0);
	else
		FragColor = vec4(Color, 1.0);
}