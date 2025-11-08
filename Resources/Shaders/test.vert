#version 450 core

layout(location = 0) in vec3 l_vertexPos;
layout(location = 1) in vec4 l_vertexColor;
layout(location = 2) in vec2 l_vertexUV;
layout(location = 3) in vec3 l_vertexNormal;

// MVP matrices
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec4 vertexColor;
out vec2 vertexUV;
out vec3 vertexNormal;     
out vec3 fragmentPosition; 

void main(void)
{
    vec4 worldPos = u_model * vec4(l_vertexPos, 1.0);
    gl_Position = u_projection * u_view * worldPos;

    vertexColor = l_vertexColor;
    vertexUV = l_vertexUV;

    mat3 normalMatrix = mat3(transpose(inverse(u_model)));
    vertexNormal = normalize(normalMatrix * l_vertexNormal);

    fragmentPosition = vec3(worldPos);
}
