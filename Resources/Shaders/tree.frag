#version 450 core

in vec2 vertexUV;
uniform sampler2D u_texture;
out vec4 fragmentColor;

void main(void)
{
    vec4 color = texture(u_texture, vertexUV);
    if (color.a < 0.1) discard; 
    fragmentColor = color;
}
