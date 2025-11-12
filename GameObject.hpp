#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>
#include "glm/glm.hpp"

class GameObject
{
private:
    std::string name;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    bool active = true;

public:
    virtual void update(float delta);
    virtual void render();

    GameObject(std::string name = "Unnamed object",
               glm::vec3 position = glm::vec3(0.0f),
               glm::vec3 rotation = glm::vec3(0.0f),
               glm::vec3 scale = glm::vec3(1.0f)); 
    ~GameObject() = default;

    void setPosition(const glm::vec3& pos);
    void setRotation(const glm::vec3& rot);
    void setScale(const glm::vec3& scl);

    glm::mat4 getModelMatrix() const;
};

#endif