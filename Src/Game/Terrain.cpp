#include "./Terrain.hpp"
#include "./GrassPatch.hpp"
#include "../Misc/Globals.hpp"
#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"
#include <cstdlib>
#include <algorithm>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"

Terrain::Terrain(int gridSize, float quadSize, int _treeCount) : vbo(GL_ARRAY_BUFFER), ebo(GL_ELEMENT_ARRAY_BUFFER), treeCount(_treeCount)
{
    std::cout << "MESSAGE: Generating base terrain..." << std::endl;

    perlinParameters = {
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        0.2f,
        4,
        0.5f,
        10.0f,
    };

    for (int i = 0; i <= gridSize; i++)
    {
        for (int j = 0; j <= gridSize; j++)
        {
            float x = -1.0f + j * quadSize;
            float z = -1.0f + i * quadSize;

            float u = (j % 2 == 0 ? 0.0f : 1.0f);
            float v = (i % 2 == 0 ? 0.0f : 1.0f);

            vertices.push_back({{x, 0.0f, z},
                                {(float)i / 10.0f, (float)i / 10.0f, (float)i / 10.0f, 1.0f},
                                {u, v},
                                {0.0f, 1.0f, 0.0f}});
        }
    }

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            int row1 = i * (gridSize + 1);
            int row2 = (i + 1) * (gridSize + 1);

            int v0 = row1 + j;
            int v1 = row2 + j;
            int v2 = row2 + j + 1;
            int v3 = row1 + j + 1;

            indices.push_back(v0);
            indices.push_back(v1);
            indices.push_back(v2);

            indices.push_back(v0);
            indices.push_back(v2);
            indices.push_back(v3);
        }
    }

    setBuffers();

    std::cout << "MESSAGE: " << gridSize << "x" << gridSize << " grid created with quad size of: " << quadSize << "." << std::endl;
    std::cout << "MESSAGE: Finished generating base terrain." << std::endl;
}

void Terrain::setBuffers()
{
    vao.bind();
    vbo.bind();

    vbo.setBufferData(vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

    vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0));
    vao.enableVAR(0);
    vao.setVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
    vao.enableVAR(1);
    vao.setVertexAttributes(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(7 * sizeof(float)));
    vao.enableVAR(2);
    vao.setVertexAttributes(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(9 * sizeof(float)));
    vao.enableVAR(3);

    ebo.bind();
    ebo.setBufferData(indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
}

void Terrain::updateBuffers()
{
    vao.bind();
    vbo.bind();

    vbo.setBufferData(vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

    vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0));
    vao.enableVAR(0);
    vao.setVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
    vao.enableVAR(1);
    vao.setVertexAttributes(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(7 * sizeof(float)));
    vao.enableVAR(2);
    vao.setVertexAttributes(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(9 * sizeof(float)));
    vao.enableVAR(3);
}

void Terrain::setRandomHeightValues()
{
    std::cout << "MESSAGE: Setting randomized terrain height values..." << std::endl;

    srand(static_cast<unsigned>(time(0)));

    for (size_t tri = 0; tri < indices.size(); tri += 3)
    {
        int val = rand() % 2;
        unsigned int i0 = indices[tri];
        unsigned int i1 = indices[tri + 1];
        unsigned int i2 = indices[tri + 2];

        vertices[i0].position.y = val;
        vertices[i1].position.y = val;
        vertices[i2].position.y = val;
    }

    updateAllNormals();
    updateBuffers();

    std::cout << "MESSAGE: Finished setting randomized terrain height values." << std::endl;
}

void Terrain::setPerlinNoiseHeightValues()
{
    std::cout << "MESSAGE: Setting perlin noise generated terrain height values..." << std::endl;

    for (auto &vertex : vertices)
    {
        float x = vertex.position.x * perlinParameters.scale;
        float z = vertex.position.z * perlinParameters.scale;

        float amp = 1.0f;
        float frequency = perlinParameters.frequency;
        float total = 0.0f;
        float maxValue = 0.0f;

        for (int i = 0; i < perlinParameters.octaves; i++)
        {
            float noise = stb_perlin_noise3(x * frequency, z * frequency, 0.0f, 0, 0, 0);
            total += noise * amp;
            maxValue += amp;

            amp *= perlinParameters.persistence;
            frequency *= 2.0f;
        }

        float h = (total / maxValue + 1.0f) * 0.5f;
        vertex.position.y = h * perlinParameters.heightScale * perlinParameters.amplitude;
    }

    generateTrees();
    updateAllNormals();
    updateBuffers();

    for (int tri = 0; tri < indices.size(); tri += 3)
    {
        glm::vec3 a, b, c;
        a = vertices.at(indices.at(tri)).position;
        b = vertices.at(indices.at(tri + 1)).position;
        c = vertices.at(indices.at(tri + 2)).position;
        auto g = std::make_unique<GrassPatch>(a, b, c, 20);
        grassPatches.push_back(std::move(g));
    }

    for (auto &g : grassPatches)
    {
        for (auto &b : g->blades)
        {
            grassInstances.push_back({b.position,
                                      b.scale,
                                      b.type});
        }
    }

    grassInstanceVBO.bind();

    grassInstanceVBO.setBufferData(
        grassInstances.size() * sizeof(GrassBlade),
        grassInstances.data(),
        GL_STATIC_DRAW);

    vao.bind();
    grassInstanceVBO.bind();

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(GrassBlade), (void *)0);
    glVertexAttribDivisor(4, 1);

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(GrassBlade), (void *)(sizeof(glm::vec3)));
    glVertexAttribDivisor(5, 1);

    glEnableVertexAttribArray(6);
    glVertexAttribIPointer(6, 1, GL_INT, sizeof(GrassBlade), (void *)(2 * sizeof(glm::vec3)));
    glVertexAttribDivisor(6, 1);
}

void Terrain::updateAllNormals()
{
    for (auto &v : vertices)
        v.normal = glm::vec3(0.0f);

    for (size_t tri = 0; tri < indices.size(); tri += 3)
    {
        unsigned int i0 = indices[tri];
        unsigned int i1 = indices[tri + 1];
        unsigned int i2 = indices[tri + 2];

        glm::vec3 p0 = vertices[i0].position;
        glm::vec3 p1 = vertices[i1].position;
        glm::vec3 p2 = vertices[i2].position;

        glm::vec3 U = p1 - p0;
        glm::vec3 V = p2 - p0;

        glm::vec3 faceNormal = glm::normalize(glm::cross(U, V));

        vertices[i0].normal += faceNormal;
        vertices[i1].normal += faceNormal;
        vertices[i2].normal += faceNormal;
    }

    for (auto &v : vertices)
        v.normal = glm::length(v.normal) > 0.0001f ? glm::normalize(v.normal) : glm::vec3(0.0f, 1.0f, 0.0f);
}

void Terrain::render()
{
    vao.bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}

void Terrain::generateTrees()
{
    if (!trees.empty())
    {
        trees.clear();
    }

    srand(static_cast<unsigned>(time(0)));
    int vertexCount = vertices.size();

    for (int i = 0; i < treeCount; i++)
    {
        int randomVertexIndex = rand() % vertexCount;
        glm::vec3 position = vertices.at(randomVertexIndex).position;

        bool duplicate = false;
        for (const auto &tptr : trees)
        {
            if (tptr->getPosition() == position)
            {
                duplicate = true;
                break;
            }
        }
        if (duplicate)
            continue;

        auto tree = std::make_unique<Tree>();
        tree->setPosition(glm::vec3(position.x, position.y + 0.4f, position.z));
        tree->setRotation(glm::vec3(0.0f, rand() % 360, 0.0f));
        trees.push_back(std::move(tree));
    }

    std::cout << "MESSAGE: Generated " << trees.size() << " trees.\n";
}

void Terrain::renderTrees()
{
    for (auto &t : trees)
    {
        t->render();
    }
}

void Terrain::renderGrass()
{
    vao.bind();
    Globals::resourceManager.getShader("grass")->use();

    Globals::resourceManager.getTexture("grass_blade_grass_1.png")->bindToUnit(0);
    Globals::resourceManager.getTexture("grass_blade_grass_2.png")->bindToUnit(1);
    Globals::resourceManager.getTexture("grass_blade_grass_3.png")->bindToUnit(2);
    Globals::resourceManager.getTexture("grass_blade_grass_4.png")->bindToUnit(3);
    Globals::resourceManager.getTexture("grass_blade_clover_1.png")->bindToUnit(4);
    Globals::resourceManager.getTexture("grass_blade_clover_2.png")->bindToUnit(5);
    Globals::resourceManager.getTexture("grass_blade_dandelion.png")->bindToUnit(6);
    Globals::resourceManager.getTexture("grass_blade_yellow_flower.png")->bindToUnit(7);

    Globals::resourceManager.getShader("grass")->setMat4(Globals::camera.getViewMatrix(), "u_view");
    Globals::resourceManager.getShader("grass")->setMat4(Globals::camera.getProjectionMatrix(), "u_projection");
    Globals::resourceManager.getShader("grass")->use();
    Globals::resourceManager.getShader("grass")->setInt(0, "u_grass1");
    Globals::resourceManager.getShader("grass")->setInt(1, "u_grass2");
    Globals::resourceManager.getShader("grass")->setInt(2, "u_grass3");
    Globals::resourceManager.getShader("grass")->setInt(3, "u_grass4");
    Globals::resourceManager.getShader("grass")->setInt(4, "u_clover1");
    Globals::resourceManager.getShader("grass")->setInt(5, "u_clover2");
    Globals::resourceManager.getShader("grass")->setInt(6, "u_dandelion");
    Globals::resourceManager.getShader("grass")->setInt(7, "u_yellowFlower");

    glDrawElementsInstanced(
        GL_TRIANGLES,
        6, 
        GL_UNSIGNED_INT,
        0,
        (GLsizei)grassInstances.size() 
    );
}
