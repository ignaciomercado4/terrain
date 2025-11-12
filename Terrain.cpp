#include "./Terrain.hpp"
#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"

#define STB_PERLIN_IMPLEMENTATION

Terrain::Terrain(int gridSize, float quadSize) : vbo(GL_ARRAY_BUFFER), ebo(GL_ELEMENT_ARRAY_BUFFER)
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

    updateAllNormals();
    updateBuffers();

    std::cout << "MESSAGE: Finished setting perlin noise generated terrain height values." << std::endl;
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


void Terrain::draw()
{
    vao.bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}
