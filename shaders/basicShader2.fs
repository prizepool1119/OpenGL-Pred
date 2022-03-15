#version 460 core

in vec3 Color;

out vec4 FragColor;

uniform float alpha;

void main()
{
	FragColor = vec4(vec3(1.0f), alpha);
}