#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include "./Utils.hpp"

std::string Utils::loadFileContents(std::string path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << path << "\n";
    }

    std::string contents;
    std::string line;
    while (getline(file, line))
    {
        contents += line + "\n";
    }

    file.close();
    return contents;
}

bool Utils::isPointInsideTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 point)
{
    float wA, wB, wC, D;

    D = glm::length(glm::cross(p2 - p1, p3 - p1));

    float areaPBC = glm::length(glm::cross(p2 - point, p3 - point));
    float areaPCA = glm::length(glm::cross(p3 - point, p1 - point));
    float areaPAB = glm::length(glm::cross(p1 - point, p2 - point));

    wA = areaPBC / D;
    wB = areaPCA / D;
    wC = areaPAB / D;
    float sum = wA + wB + wC;
    const float eps = 1e-4f;

    if (fabs(sum - 1.0f) > eps)
        return false;

        return (wA >= -eps && wB >= -eps && wC >= -eps &&
            wA <= 1 + eps && wB <= 1 + eps && wC <= 1 + eps);
}