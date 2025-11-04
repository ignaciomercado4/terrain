#version 450 core

out vec4 fragColor;
in vec4 vertexColor;

void main(void)
{
    fragColor = vertexColor;
}
