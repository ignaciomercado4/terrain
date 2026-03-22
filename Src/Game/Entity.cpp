#include "./Entity.hpp"

void Entity::setPosition(const glm::vec3 &pos)
{
    position = pos;
}

void Entity::setRotation(const glm::vec3 &rot)
{
    rotation = rot;
}

void Entity::setScale(const glm::vec3 &scl)
{
    scale = scl;
}

glm::vec3 Entity::getPosition() const
{
    return position;
}

glm::vec3 Entity::getRotation() const
{
    return rotation;
}

glm::vec3 Entity::getScale() const
{
    return scale;
}

glm::mat4 Entity::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
    model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
    model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
    model = glm::scale(model, scale);
    return model;
}