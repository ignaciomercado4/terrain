#ifndef UTILS_HPP
#define UTILS_HPP

#include "glm/glm.hpp"
#include <iostream>

class Utils
{
    private:
    public:
    static std::string loadFileContents(std::string path);
    static bool isPointInsideTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 point);
};

#endif