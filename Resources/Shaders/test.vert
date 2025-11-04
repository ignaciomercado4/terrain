#version 450 core

layout(location = 0) in vec3 l_vertexPos;
layout(location = 1) in vec4 l_vertexColor;

uniform mat4 u_mvp;
out vec4 vertexColor;

void main(void)
{
    gl_Position = u_mvp * vec4(l_vertexPos, 1.0f);
    vertexColor = l_vertexColor;
}