#include "./Grass.hpp"
#include "../Graphics/Vertex.hpp"
#include "../Misc/Globals.hpp"
#include <random>

Grass::Grass(int instancesPerTriangle, std::vector<Vertex> &terrainVerts, std::vector<unsigned int> &terrainIndices) : maxInstancesPerTri(instancesPerTriangle), ebo(GL_ELEMENT_ARRAY_BUFFER), vbo(GL_ARRAY_BUFFER)
{
    for (int i = 0; i < terrainIndices.size(); i += 3)
    {
        glm::vec3 a = terrainVerts.at(terrainIndices.at(i)).position;
        glm::vec3 b = terrainVerts.at(terrainIndices.at(i + 1)).position;
        glm::vec3 c = terrainVerts.at(terrainIndices.at(i + 2)).position;

        populateTriangle(a, b, c);
    }

    std::cout << "MESSAGE: Generated " << instances.size() << " grass instances." << std::endl;
    setBuffers();
}

void Grass::setBuffers()
{
    vao.bind();
    vbo.bind();
    vbo.setBufferData(vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    vao.enableVAR(0);

    vao.setVertexAttributes(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
    vao.enableVAR(2);

    ebo.bind();
    ebo.setBufferData(indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(VegetationInstance), instances.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VegetationInstance), (void *)offsetof(VegetationInstance, position));
    glVertexAttribDivisor(4, 1);

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(VegetationInstance), (void *)offsetof(VegetationInstance, scale));
    glVertexAttribDivisor(5, 1);

    glEnableVertexAttribArray(6);
    glVertexAttribIPointer(6, 1, GL_INT,
                           sizeof(VegetationInstance),
                           (void *)offsetof(VegetationInstance, type));
    glVertexAttribDivisor(6, 1);
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

        if (u + v > 1.0f)
        {
            u = 1.0f - u;
            v = 1.0f - v;
        }

        float typeProbability = dist(rng);

        glm::vec3 p = a + u * (b - a) + v * (c - a);
        glm::vec3 s = glm::vec3(0.03f, 0.05f, 0.03f);

        VegetationType t;

        if (typeProbability < 0.05f)
        {
            t = YELLOW_FLOWER;
        }
        else if (typeProbability < 0.15f)
        {
            t = (dist(rng) < 0.5f) ? CLOVER_1 : CLOVER_2;
        }
        else if (typeProbability < 0.30f)
        {
            t = GRASS_1;
        }
        else if (typeProbability < 0.50f)
        {
            t = GRASS_2;
        }
        else if (typeProbability < 0.70f)
        {
            t = GRASS_3;
        }
        else
        {
            t = GRASS_4;
        }

        VegetationInstance ins = {p, s, t};
        instances.push_back(ins);
    }
}

void Grass::renderInstances()
{
    vao.bind();
    Globals::resourceManager.getShader("grass")->use();
    Globals::resourceManager.getShader("grass")->setMat4(Globals::camera.getViewMatrix(), "u_view");
    Globals::resourceManager.getShader("grass")->setMat4(Globals::camera.getProjectionMatrix(), "u_projection");
    Globals::resourceManager.getTexture("grass_blade_grass_1.png")->bindToUnit(3);
    Globals::resourceManager.getShader("grass")->setInt(3, "u_grassTexture1");

    Globals::resourceManager.getTexture("grass_blade_grass_2.png")->bindToUnit(4);
    Globals::resourceManager.getShader("grass")->setInt(4, "u_grassTexture2");

    Globals::resourceManager.getTexture("grass_blade_grass_3.png")->bindToUnit(5);
    Globals::resourceManager.getShader("grass")->setInt(5, "u_grassTexture3");

    Globals::resourceManager.getTexture("grass_blade_grass_4.png")->bindToUnit(6);
    Globals::resourceManager.getShader("grass")->setInt(6, "u_grassTexture4");

    Globals::resourceManager.getTexture("grass_blade_clover_1.png")->bindToUnit(7);
    Globals::resourceManager.getShader("grass")->setInt(7, "u_cloverTexture1");

    Globals::resourceManager.getTexture("grass_blade_clover_2.png")->bindToUnit(8);
    Globals::resourceManager.getShader("grass")->setInt(8, "u_cloverTexture2");

    Globals::resourceManager.getTexture("grass_blade_yellow_flower.png")->bindToUnit(9);
    Globals::resourceManager.getShader("grass")->setInt(9, "u_yellowFlowerTexture");

    glDisable(GL_CULL_FACE);

    std::cout << "Size of VegetationInstance: " << sizeof(VegetationInstance) << std::endl;

    glDrawElementsInstanced(
        GL_TRIANGLES,
        indices.size(),
        GL_UNSIGNED_INT,
        0,
        instances.size());
}
