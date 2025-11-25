#include "./Grass.hpp"
#include <random>

Grass::Grass(int instancesPerTriangle, std::vector<Vertex> terrainVerts, std::vector<unsigned int> terrainIndices) : maxInstancesPerTri(instancesPerTriangle)
{
    for (int i = 0; i < terrainIndices.size(); i += 3)
    {
        glm::vec3 a = terrainVerts.at(terrainIndices.at(i)).position;
        glm::vec3 b = terrainVerts.at(terrainIndices.at(i + 1)).position;
        glm::vec3 c = terrainVerts.at(terrainIndices.at(i + 2)).position;

        std::cout << "------Vertices pos------" << std::endl;
        std::cout << glm::to_string(a) << std::endl;
        std::cout << glm::to_string(b) << std::endl;
        std::cout << glm::to_string(c) << std::endl;
        std::cout << "------------------------" << std::endl;
        populateTriangle(a, b, c);
    }
}

void Grass::populateTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
    // P=A+u(B−A)+v(C−A) u&v=rand(0,1)
    for (int j = 0; j < maxInstancesPerTri; j++)
    {
        static std::default_random_engine rng;
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        float u = dist(rng);
        float v = dist(rng);

        glm::vec3 p = a + u * (b - a) + v * (c - a);
        std::cout << glm::to_string(p) << std::endl;
        glm::vec3 s = glm::vec3(0.1f, 0.1f, 0.1f);
        VegetationInstance ins = {p, s, GRASS_1};
        instances.push_back(ins);
    }
}