#version 330 core

in vec2 UV;
in float instanceHeight;

flat in int type;

out vec4 FragColor;

uniform sampler2D u_grassTexture1;
uniform sampler2D u_grassTexture2;
uniform sampler2D u_grassTexture3;
uniform sampler2D u_grassTexture4;
uniform sampler2D u_cloverTexture1;
uniform sampler2D u_cloverTexture2;
uniform sampler2D u_yellowFlowerTexture;
uniform sampler2D u_bushTexture1;
uniform sampler2D u_bushTexture2;


void main() {
    vec4 color;

    switch(type) {
        case 0:
            color = texture(u_grassTexture1, UV);
            break;
        case 1:
            color = texture(u_grassTexture2, UV);
            break;
        case 2:
            color = texture(u_grassTexture3, UV);
            break;
        case 3:
            color = texture(u_grassTexture4, UV);
            break;
        case 4:
            color = texture(u_yellowFlowerTexture, UV);
            break;
        case 5:
            color = texture(u_cloverTexture1, UV);
            break;
        case 6:
            color = texture(u_cloverTexture2, UV);
            break;
        case 7:
            color = texture(u_bushTexture1, UV);
            break;
        case 8:
            color = texture(u_bushTexture2, UV);
            break;
    }

    if(color.a < 0.1)
        discard;
    if(color.r < 0.1 && color.g < 0.1 && color.b < 0.1)
        discard;
    if(color.r > 0.99 && color.g > 0.99 && color.b > 0.99)
        discard;

    if(instanceHeight > 4.5 || instanceHeight > 4.4 || instanceHeight > 4.3) {
        discard;
    }

    FragColor = color;
}
