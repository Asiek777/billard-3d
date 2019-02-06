#version 330 core
out vec4 FragColor;  

in vec3 Normal;
in vec3 FragPos;

uniform vec3 ballColor;
uniform vec3 lightPos; 
uniform vec3 viewPos; 


void main()
{
	float ambient = 0.1;	

	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuse = max(dot(normal, lightDir), 0.0);
	
	float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
	float specular = specularStrength * spec;

    vec3 result = (ambient + diffuse + specular) * ballColor;
    FragColor = vec4(result, 1.0);

	//vec3 toLight = vec3(0.8,0.6,0.0);
	//vec3 light = Normal * toLight;
	//float lightLevel = (light.x + light.y + light.z) * 0.9;
	//lightLevel += 0.1;
    //FragColor = vec4(lightLevel * ballColor ,1.0);
}