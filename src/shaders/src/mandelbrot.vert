#version 430 core
layout (location = 0) in vec3 aPos;

uniform vec3 objectColor = vec3(1.f);
uniform mat4 model = mat4(1.f);
uniform mat4 view = mat4(1.f);
uniform mat4 projection = mat4(1.f);

out vec2 pos;

void main()
{
	pos = aPos.xy;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}