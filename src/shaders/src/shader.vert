#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) uniform mat4 projection = mat4(
	vec4(0.5f, 0.0f, 0.0f, 0.0f),
    vec4(0.0f, 0.5f, 0.0f, 0.0f),
    vec4(0.0f, 0.0f, 0.5f, 0.0f),
    vec4(0.0f, 0.0f, 0.0f, 1.0f)
);


void main()
{
    gl_Position = projection * vec4(position, 1.0);
}