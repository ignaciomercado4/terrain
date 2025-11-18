#include "./GrassPatch.hpp"
#include "../Misc/Globals.hpp"
#include <random>
#include <iostream>

GrassPatch::GrassPatch(glm::vec3 a, glm::vec3 b, glm::vec3 c, int _maxBlades) : maxBlades(_maxBlades)
{
    triangleVertices[0] = a;
    triangleVertices[1] = b;
    triangleVertices[2] = c;
    blades.clear();
    blades.reserve(maxBlades);

    for (int i = 0; i < maxBlades; i++)
    {
        std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<float> distUV(0.0f, 1.0f);

        float u = distUV(rng);
        float v = distUV(rng);
        float typeDeterminator = distUV(rng);

        if (u + v > 1.0f)
        {
            u = 1.0f - u;
            v = 1.0f - v;
        }

        glm::vec3 p = a + u * (b - a) + v * (c - a);
        p.y += 0.07f;

        std::uniform_real_distribution<float> distS(0.01f, 0.02f);
        glm::vec3 s(0.01f, distS(rng), 0.01f);

        GrassBladeType t;

        if (typeDeterminator < 0.02f)
        {
            t = DANDELION;
        }
        else if (typeDeterminator < 0.04f)
        {
            t = YELLOW_FLOWER;
        }
        else if (typeDeterminator < 0.06f)
        {
            t = CLOVER_1;
        }
        else if (typeDeterminator < 0.08f)
        {
            t = CLOVER_2;
        }
        else if (typeDeterminator < 0.3f)
        {
            t = GRASS_1;
        }
        else if (typeDeterminator < 0.5f)
        {
            t = GRASS_2;
        }
        else if (typeDeterminator < 0.8f)
        {
            t = GRASS_3;
        }
        else
        {
            t = GRASS_4;
        }

        GrassBlade b = {p, s, t};

        blades.push_back(b);
    }
}
