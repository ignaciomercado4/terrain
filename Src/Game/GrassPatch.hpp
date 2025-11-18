#ifndef GRASSPATCH_HPP
#define GRASSPATCH_HPP

#include "glm/glm.hpp"
#include <vector>
#include "../Graphics/VAO.hpp"
#include "../Graphics/VBO.hpp"
#include "../Graphics/Vertex.hpp"

enum GrassBladeType
{
    GRASS_1,
    GRASS_2,
    GRASS_3,
    GRASS_4,
    CLOVER_1,
    CLOVER_2,
    DANDELION,
    YELLOW_FLOWER
};

struct GrassBlade
{
    glm::vec3 position;
    glm::vec3 scale;
    GrassBladeType type;
};

class GrassPatch
{
private:
    glm::vec3 triangleVertices[3];
    int maxBlades;
    std::vector<Vertex> vertices = {
        {{-0.25f, 0.0f, 0.0f}, {1, 1, 1, 1}, {0, 0}, {0, 0, 1}},
        {{0.25f, 0.0f, 0.0f}, {1, 1, 1, 1}, {1, 0}, {0, 0, 1}},
        {{0.25f, 1.0f, 0.0f}, {1, 1, 1, 1}, {1, 1}, {0, 0, 1}},
        {{-0.25f, 1.0f, 0.0f}, {1, 1, 1, 1}, {0, 1}, {0, 0, 1}}};

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0};

public:
    GrassPatch(glm::vec3 a, glm::vec3 b, glm::vec3 c, int _maxBlades);
    std::vector<GrassBlade> blades;
};

#endif