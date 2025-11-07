#include "./Terrain.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#define STB_PERLIN_IMPLEMENTATION
#include <stb/stb_perlin.h>

Terrain::Terrain(float gridSize, float quadSize)
{
    for (int i = 0; i <= gridSize; i++)
    {
        for (int j = 0; j <= gridSize; j++)
        {
            float x = -1.0f + j * quadSize;
            float z = -1.0f + i * quadSize;
            float u = (float)(j % 2);
            float v = (float)(i % 2);

            u = (float)(j % 2 == 0 ? 0.0f : 1.0f);
            v = (float)(i % 2 == 0 ? 0.0f : 1.0f);

            vertices.push_back({{x, 0.0f, z}, {(float)i / 10.0f, (float)i / 10.0f, (float)i / 10.0f, 1.0f}, {u, v}});
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
    };

    std::cout << "MESSAGE: " << gridSize << "x" << gridSize << " grid created with quad size of: " << quadSize << "." << std::endl;
}

void Terrain::setRandomHeightValues()
{
    srand((unsigned)time(0));

    for (int tri = 0; tri < indices.size(); tri += 3)
    {
        int val;
        val = (rand() % 2);
        unsigned int i0 = indices[tri];
        unsigned int i1 = indices[tri + 1];
        unsigned int i2 = indices[tri + 2];

        vertices[i0].position.y = val;
        vertices[i1].position.y = val;
        vertices[i2].position.y = val;
    }
}

void Terrain::setPerlinNoiseHeightValues()
{
    float scale = 0.2f;        // controls how zoomed-in the terrain looks
    int octaves = 4;           // number of noise layers
    float persistence = 0.5f;  // amplitude falloff per octave
    float heightScale = 10.0f; // vertical exaggeration

    for (auto &vertex : vertices)
    {
        float x = vertex.position.x * scale;
        float z = vertex.position.z * scale;

        // fractal (multi-octave) perlin noise 
        float amplitude = 1.0f;
        float frequency = 1.0f;
        float total = 0.0f;
        float maxValue = 0.0f;

        for (int i = 0; i < octaves; i++)
        {
            float noise = stb_perlin_noise3(x * frequency, z * frequency, 0.0f, 0, 0, 0);
            total += noise * amplitude;
            maxValue += amplitude;
            amplitude *= persistence;
            frequency *= 2.0f;
        }

        float h = (total / maxValue + 1.0f) * 0.5f; // normalize to 0,1
        vertex.position.y = h * heightScale;
    }
}