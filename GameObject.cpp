#include "./GameObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

GameObject::GameObject(std::string name,
                       glm::vec3 position,
                       glm::vec3 rotation,
                       glm::vec3 scale) : name(name),
                                          position(position),
                                          rotation(rotation),
                                          scale(scale) {}

void GameObject::render() {}

void GameObject::update(float delta) {}

void GameObject::setPosition(const glm::vec3 &pos) { position = pos; }

glm::vec3 GameObject::getPosition() const { return position; }

void  GameObject::setRotation(const glm::vec3 &rot) { rotation = rot; }

glm::vec3 GameObject::getRotation() const { return rotation; }

void GameObject::setScale(const glm::vec3 &scl) { scale = scl; }

glm::vec3 GameObject::getScale() const { return scale; }

glm::mat4 GameObject::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
    model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
    model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
    model = glm::scale(model, scale);
    return model;
}
