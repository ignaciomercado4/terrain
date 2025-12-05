#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <fstream>
#include "./Utils.hpp"
#include "./Globals.hpp"

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

void Utils::updateTiming()
{
    float currentFrame = (float)glfwGetTime();
    Globals::deltaTime = currentFrame - Globals::lastFrame;
    Globals::lastFrame = currentFrame;

    Globals::fps = 1.0f / Globals::deltaTime;
}

void Utils::checkGLError(const char* context) {
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch(err) {
            case GL_INVALID_ENUM: error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE: error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION: error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW: error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW: error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY: error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default: error = std::to_string(err); break;
        }
        std::cout << "OpenGL error in " << context << ": " << error << " (0x" << std::hex << err << ")" << std::dec << std::endl;
    }
}

std::string Utils::getDirectory(std::string path)
{
     
    size_t pos1 = path.find_last_of('/');
    size_t pos2 = path.find_last_of('\\');

    size_t pos = std::string::npos;

    if (pos1 != std::string::npos && pos2 != std::string::npos)
        pos = std::max(pos1, pos2);
    else if (pos1 != std::string::npos)
        pos = pos1;
    else if (pos2 != std::string::npos)
        pos = pos2;

    if (pos == std::string::npos)
        return "."; 

    return path.substr(0, pos);
}