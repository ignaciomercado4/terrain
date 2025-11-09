#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>
#include "./Vertex.hpp"
#include "./VAO.hpp"
#include "./VBO.hpp"

class Terrain
{
private:
    VAO vao;
    VBO vbo;
    VBO ebo;
    void setBuffers();

public:
    void updateAllNormals();
    Terrain(int gridSize, float quadSize);
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    void updateBuffers();
    void setRandomHeightValues();
    void setPerlinNoiseHeightValues();
};

#endif
