#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "./Input.hpp"
#include "./Camera.hpp"
#include "./Vertex.hpp"
#include "./Utils.hpp"

float SPEED = 0.05f;
float ROTATION_SPEED = 2.0f;

void Input::update(Window &window, Camera &camera, glm::mat4 model, std::vector<Vertex> &vertices)
{
    if (glfwGetKey(window.getWindowPointer(), GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.moveForward(SPEED);
    }
    if (glfwGetKey(window.getWindowPointer(), GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.moveBackward(SPEED);
    }
    if (glfwGetKey(window.getWindowPointer(), GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.moveLeft(SPEED);
    }
    if (glfwGetKey(window.getWindowPointer(), GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.moveRight(SPEED);
    }
    if (glfwGetKey(window.getWindowPointer(), GLFW_KEY_UP) == GLFW_PRESS)
    {
        camera.addPitch(ROTATION_SPEED);
    }
    if (glfwGetKey(window.getWindowPointer(), GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        camera.addPitch(-ROTATION_SPEED);
    }
    if (glfwGetKey(window.getWindowPointer(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        camera.addYaw(ROTATION_SPEED);
    }
    if (glfwGetKey(window.getWindowPointer(), GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        camera.addYaw(-ROTATION_SPEED);
    }
    if (glfwGetKey(window.getWindowPointer(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        // get mouse x,y position
        double mouseX, mouseY;
        glfwGetCursorPos(window.getWindowPointer(), &mouseX, &mouseY);

        // normalize x,y to NDC (-1; 1) & make it a vec3
        float x = (2.0f * mouseX) / window.width - 1.0f;
        float y = 1.0f - (2.0f * mouseY) / window.height;
        float z = 1.0f;
        glm::vec3 rayNDS = glm::vec3(x, y, z);

        // create a vector in clip space
        glm::vec4 rayClip = glm::vec4(rayNDS.x, rayNDS.y, -1.0, 1.0);

        // transform ray to camera eye space
        glm::vec4 rayEye = glm::inverse(camera.getProjectionMatrix()) * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0, 0.0);

        // transform ray to world space and normalize
        auto t = glm::inverse(camera.getViewMatrix()) * rayEye;
        glm::vec3 rayWorld(t.x, t.y, t.z);
        rayWorld = glm::normalize(rayWorld);

        std::cout << "VECTOR: " << rayWorld.x << " " << rayWorld.y << " " << rayWorld.z << "\n";

        glm::vec3 rayOrigin = camera.getEye();
        glm::vec3 rayDir = glm::normalize(rayWorld);

        glm::vec3 planeNormal = glm::normalize(glm::mat3(glm::transpose(glm::inverse(model))) * glm::vec3(0, 1, 0));
        glm::vec3 planePoint = glm::vec3(model * glm::vec4(0, 0, 0, 1));

        float denom = glm::dot(planeNormal, rayDir);
        const float EPS = 1e-6f;
        glm::vec3 hitPoint;
        if (fabs(denom) > EPS)
        {
            float t = glm::dot(planePoint - rayOrigin, planeNormal) / denom;
            if (t >= 0.0f)
            {
                hitPoint = rayOrigin + t * rayDir;
                std::cout << "HIT at t=" << t << " -> ("
                          << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << ")\n";

                for (int i = 0; i < vertices.size(); i += 3)
                {
                    glm::vec3 v1_world = glm::vec3(model * glm::vec4(vertices.at(i).position, 1.0f));
                    glm::vec3 v2_world = glm::vec3(model * glm::vec4(vertices.at(i + 1).position, 1.0f));
                    glm::vec3 v3_world = glm::vec3(model * glm::vec4(vertices.at(i + 2).position, 1.0f));

                    bool isInside = Utils::isPointInsideTriangle(v1_world, v2_world, v3_world, hitPoint);
                    if (isInside)
                    {
                        std::cout << "Hit inside triangle\n";
                    }
                }
            }
            else
            {
                std::cout << "Intersection behind origin (t < 0)\n";
            }
        }
        else
        {
            std::cout << "Ray parallel to plane\n";
        }
    }
}