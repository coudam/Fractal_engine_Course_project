#version 430 core

layout (location = 0) in vec3 pointCor;
layout (location = 2) in vec3 normalIn;

layout (location = 1) uniform mat4 view ;
layout (location = 3) uniform mat4 model = mat4(0.1f);
layout (location = 4) uniform mat4 projection = mat4(1.f);

out vec3 normal;
out vec3 pointPos;

void main()
{
	pointPos = vec3(model * vec4(pointCor, 1.0));

    gl_Position = projection * view * vec4(pointPos, 1.0);
    
    normal = normalIn;
}
