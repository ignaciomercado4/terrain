#version 450 core

in vec2 vertexUV;
flat in int bladeType;

out vec4 fragmentColor;

uniform sampler2D u_grass1;
uniform sampler2D u_grass2;
uniform sampler2D u_grass3;
uniform sampler2D u_grass4;
uniform sampler2D u_clover1;
uniform sampler2D u_clover2;
uniform sampler2D u_dandelion;
uniform sampler2D u_yellowFlower;

vec4 getTextureByType(int t, vec2 uv)
{
    switch(t)
    {
        case 0: return texture(u_grass1, uv);
        case 1: return texture(u_grass2, uv);
        case 2: return texture(u_grass3, uv);
        case 3: return texture(u_grass4, uv);
        case 4: return texture(u_clover1, uv);
        case 5: return texture(u_clover2, uv);
        case 6: return texture(u_dandelion, uv);
        case 7: return texture(u_yellowFlower, uv);
    }
    return texture(u_grass1, uv);
}

void main()
{
    vec4 color = getTextureByType(bladeType, vertexUV);

    if (color.a < 0.1) discard;

    if (color.r > 0.99 && color.g > 0.99 && color.b > 0.99) discard;

    fragmentColor = color;
}
