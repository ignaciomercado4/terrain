#ifndef GRASS_HPP
#define GRASS_HPP

#include "../Misc/Common.hpp"
#include "../Graphics/Vertex.hpp"
#include "../Graphics/VAO.hpp"
#include "../Graphics/VBO.hpp"
#include <vector>

enum VegetationType
{
    GRASS_1
};

struct VegetationInstance
{
    glm::vec3 position;
    glm::vec3 scale;
    VegetationType type;
};

class Grass
{
private:
    VAO vao;
    VBO vbo;
    VBO ebo;
    unsigned int instanceVBO;

    std::vector<Vertex> vertices = {
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}};

    std::vector<unsigned int> indices = {
        0, 1, 2, 0, 2, 3};
    
    int maxInstancesPerTri;
    void populateTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    void setBuffers();

public:
    std::vector<VegetationInstance> instances;
    Grass(int instancesPerTriangle, std::vector<Vertex>& terrainVerts, std::vector<unsigned int>& terrainIndices);
    void renderInstances();
};

#endif