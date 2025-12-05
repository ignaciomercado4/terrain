#version 450 core

layout(location = 0) in vec3 l_vertexPos;
layout(location = 1) in vec4 l_vertexColor;
layout(location = 2) in vec2 l_vertexUV;
layout(location = 3) in vec3 l_vertexNormal;

out vec3 v_fragPos;
out vec3 v_normal;
out vec2 v_uv;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() 
{
    vec4 worldPos = u_model * vec4(l_vertexPos, 1.0);

    v_fragPos = worldPos.xyz;
    v_normal  = mat3(transpose(inverse(u_model))) * l_vertexNormal;
    v_uv = l_vertexUV;

    gl_Position = u_projection * u_view * worldPos;
}
