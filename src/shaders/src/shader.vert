#version 330 core

layout (location = 0) in vec3 position;
uniform mat4 translate = mat4(
	vec4(0.5f, 0.0f, 0.0f, 0.0f),
    vec4(0.0f, 0.5f, 0.0f, 0.0f),
    vec4(0.0f, 0.0f, 0.5f, 0.0f),
    vec4(0.0f, 0.0f, 0.0f, 1.0f)
);

void main()
{
    gl_Position = translate * vec4(position, 1.0);
}