#version 450 core

uniform vec3 u_debugColor;
out vec4 fragmentColor;

void main()
{
    fragmentColor = vec4(u_debugColor, 1.0f);
}