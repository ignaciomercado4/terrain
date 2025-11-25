#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>
#include "../Graphics/Vertex.hpp"
#include "../Graphics/VAO.hpp"
#include "../Graphics/VBO.hpp"
#include "./Tree.hpp"
#include "./Grass.hpp"
#include <memory>

struct perlinParams
{
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float total = 0.0f;
    float maxValue = 0.0f;
    float scale = 0.2f;       // controls how zoomed-in the terrain looks
    int octaves = 4;          // number of noise layers
    float persistence = 0.5f; // amplitude falloff per octave
    float heightScale = 10.0f;
};

// Toppa' the line
class Terrain
{
    private:
    VAO vao;
    VBO vbo;
    VBO ebo;

    VBO grassInstanceVBO;
    
    void setBuffers();
    int treeCount;
    void generateTrees();
    Grass* grass = nullptr;
    
    public:
    Terrain(int gridSize, float quadSize, int treeCount);
    std::vector<std::unique_ptr<Tree>> trees;
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    perlinParams perlinParameters;
    
    void updateAllNormals();
    void updateBuffers();
    void setRandomHeightValues();
    void setPerlinNoiseHeightValues();
    void populateVegetationInstances();

    void renderTrees();
    void render();
};

#endif
