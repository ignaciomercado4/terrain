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

void main() {
    vec4 color;

    if(type == 0) {
        color = texture(u_grassTexture1, UV);
    }
    if(type == 1) {

        color = texture(u_grassTexture2, UV);
    }
    if(type == 2) {

        color = texture(u_grassTexture3, UV);
    }
    if(type == 3) {

        color = texture(u_grassTexture4, UV);
    }
    if(type == 4) {

        color = texture(u_yellowFlowerTexture, UV);
    }
    if(type == 5) {

        color = texture(u_cloverTexture1, UV);
    }
    if(type == 6) {

        color = texture(u_cloverTexture2, UV);
    }

    if(color.a < 0.1)
        discard;
    if(color.r < 0.1 && color.g < 0.1 && color.b < 0.1)
        discard;
    if(color.r > 0.99 && color.g > 0.99 && color.b > 0.99)
        discard;

    if(instanceHeight > 4.5) {
        discard;
    }

    FragColor = color;
}
