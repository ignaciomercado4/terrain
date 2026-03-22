#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include "../Misc/Common.hpp"

class Entity
{
private:
    int ID;
    glm::mat4 modelMatrix;
    glm::vec3 position, rotation, scale;

public:
    
    void setPosition(const glm::vec3& pos);
    void setRotation(const glm::vec3& rot);
    void setScale(const glm::vec3& scl);
    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;

    glm::mat4 getModelMatrix() const;

};

#endif