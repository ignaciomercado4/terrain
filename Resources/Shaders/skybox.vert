#version 330 core
layout (location = 0) in vec3 l_vertexPostion;

out vec3 UV;

uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
    UV = l_vertexPostion;
    gl_Position = u_projection * u_view * vec4(l_vertexPostion, 1.0);
}