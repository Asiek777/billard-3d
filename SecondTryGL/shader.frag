#version 330 core
out vec4 FragColor;  

in vec2 TexCoord;
in float dist;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), vec4(0.5, 0.5, 0.5, 1.0), min(dist,1));
}