#version 330 core

layout(location = 0) in vec3 l_vertexPosition;
layout(location = 2) in vec2 l_UV;
layout(location = 4) in vec3 l_instancePosition;
layout(location = 5) in vec3 l_instanceScale;
layout(location = 6) in int l_instanceType;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform vec3 u_cameraPos;
uniform float u_maxCullDistance; 

out vec2 UV;
out float instanceHeight;
flat out int type;

void main() 
{
    // distance culling 
    float dist = distance(l_instancePosition, u_cameraPos);

    if (dist > u_maxCullDistance) 
    {
        gl_Position = vec4(2.0, 2.0, 2.0, 1.0);
        UV = l_UV;
        instanceHeight = l_instancePosition.y;
        type = l_instanceType;
        return;
    }

    // back again
    vec3 world = l_instancePosition + l_vertexPosition * l_instanceScale;
    gl_Position = u_projection * u_view * vec4(world, 1.0);

    UV = l_UV;
    instanceHeight = l_instancePosition.y;
    type = l_instanceType;
}
