#version 450 core

layout(location = 0) in vec3 l_vertexPos;
layout(location = 1) in vec4 l_vertexColor;
layout(location = 2) in vec2 l_vertexUV;
layout(location = 3) in vec3 l_vertexNormal;

layout(location = 4) in vec3 instancePosition;
layout(location = 5) in vec3 instanceScale;
layout(location = 6) in int  instanceType;

uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 vertexUV;
flat out int bladeType;

void main()
{
    mat4 S = mat4(1.0);
    S[0][0] = instanceScale.x;
    S[1][1] = instanceScale.y;
    S[2][2] = instanceScale.z;

    mat4 T = mat4(1.0);
    T[3][0] = instancePosition.x;
    T[3][1] = instancePosition.y;
    T[3][2] = instancePosition.z;

    mat4 model = T * S;

    vec4 worldPos = model * vec4(l_vertexPos, 1.0);

    gl_Position = u_projection * u_view * worldPos;

    vertexUV = l_vertexUV;
    bladeType = instanceType; 
}
