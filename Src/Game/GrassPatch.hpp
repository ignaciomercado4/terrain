#ifndef GRASSPATCH_HPP
#define GRASSPATCH_HPP

#include "glm/glm.hpp"
#include <vector>
#include "../Graphics/VAO.hpp"
#include "../Graphics/VBO.hpp"
#include "../Graphics/Vertex.hpp"

class GrassPatch
{
private:
    glm::vec3 triangleVertices[3];
    std::vector<glm::vec3> bladePositions;
    int maxBlades;
    
    std::vector<Vertex> vertices = {
        {{-1.0f, -2.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{1.0f, -2.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{1.0f, 2.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{-1.0f, 2.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}};
    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0};
    
    VBO vbo;
    VAO vao;
    VBO ebo;

public:
    GrassPatch(glm::vec3 a, glm::vec3 b, glm::vec3 c, int _maxBlades);
    void renderNotInstanced();
};

#endif