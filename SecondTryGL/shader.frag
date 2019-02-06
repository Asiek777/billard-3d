#version 330 core
uniform vec3 color;

out vec4 FragColor;  

in vec3 Normal;
in vec3 FragPos;


void main()
{
	vec3 toLight = vec3(0.8,0.6,0.0);
	vec3 light = Normal * toLight;
	float lightLevel = (light.x + light.y + light.z) * 0.9;
	lightLevel += 0.1;
    FragColor = vec4(lightLevel * color ,1.0);
}