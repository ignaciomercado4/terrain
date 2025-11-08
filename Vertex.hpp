#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 uv;
    glm::vec3 normal;
};

#endif