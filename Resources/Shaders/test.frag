#version 450 core

out vec4 fragColor;
in vec4 vertexColor;
in vec2 vertexUV;
uniform sampler2D u_texture;

void main(void)
{
    fragColor = texture(u_texture, vertexUV);
}
