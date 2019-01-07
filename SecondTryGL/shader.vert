#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; 
layout (location = 2) in vec2 aTexCoord;
uniform float greenValue;
  
out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
	if(aColor.g == 0)
		ourColor = aColor;
	else
		ourColor = vec3(aColor.r, greenValue, aColor.b);
	TexCoord = aTexCoord;
}       