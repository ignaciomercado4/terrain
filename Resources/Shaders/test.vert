#version 450 core

layout(location = 0) in vec3 l_vertexPos;

uniform mat4 u_mvp;

void main(void)
{
    gl_Position = u_mvp * vec4(l_vertexPos, 1.0f);
}