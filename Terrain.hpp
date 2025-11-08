#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include "./Vertex.hpp"

class Terrain
{
    private:
    //
    public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Terrain(float gridSize, float quadSize);
    void setRandomHeightValues();
    void setPerlinNoiseHeightValues();
    void updateAllNormals();
    
};
#endif