#version 460 core

uniform vec3 lightColor;
uniform vec3 lightDir;
uniform vec3 viewPos;

in vec3 Color;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

out vec4 FragColor;

void main()
{
	vec3 norm = normalize(Normal);

	float ambientStrength = 0.2f;
	vec3 ambient = ambientStrength * lightColor * vec3(texture(texture_diffuse1, TexCoords));

	float diff = max(dot(norm, normalize(-lightDir)), 0f);
	vec3 diffuse = diff * lightColor * vec3(texture(texture_diffuse1, TexCoords));

	float specularStrength = 0.6f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(normalize(lightDir), norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor * vec3(texture(texture_specular1, TexCoords));

	vec3 result = (diffuse + ambient + specular);
	FragColor = vec4(result, 1.0f);
}