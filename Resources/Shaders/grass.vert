#version 330 core

layout(location = 0) in vec3 l_vertexPosition;
layout(location = 2) in vec2 l_UV;
layout(location = 4) in vec3 l_instancePosition;   // instancia position
layout(location = 5) in vec3 l_instanceScale; // instancia scale

uniform mat4 u_projection;
uniform mat4 u_view;

out vec2 UV;

void main()
{
    // coloca el quad EN la posición de la instancia
    vec3 world = l_instancePosition + l_vertexPosition * l_instanceScale;

    gl_Position = u_projection * u_view * vec4(world, 1.0);

    UV = l_UV;
}
