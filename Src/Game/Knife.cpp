#include "./Knife.hpp"
#include "../Misc/Globals.hpp"

Knife::Knife() : Item(ITEM_TYPE::WEAPON)
{
    setPosition(glm::vec3(0.0f));
    setScale(glm::vec3(2.0f));
    model = Globals::resourceManager.getModel("Knife");
}

void Knife::updatePosition()
{
    glm::vec3 pos(Globals::camera.getEye());
    pos.z -= 0.5;
    setPosition(pos);
}

void Knife::render()
{
    float forwardOffset = 0.5f;
    float rightOffset = 0.5f;
    float downOffset = -0.4f;
    glm::mat4 view = Globals::camera.getViewMatrix();

    glm::vec3 camPos = Globals::camera.getEye();
    glm::vec3 camRight = glm::vec3(glm::transpose(view)[0]);
    glm::vec3 camUp = glm::vec3(glm::transpose(view)[1]);
    glm::vec3 camFront = -glm::vec3(glm::transpose(view)[2]);

    glm::vec3 knifePos = camPos + camFront * forwardOffset + camRight * rightOffset + camUp * downOffset;

    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, knifePos);

    // Apply camera rotation (inverse of view rotation)
    glm::mat3 camRot = glm::mat3(glm::transpose(view));
    modelMat *= glm::mat4(camRot);

    modelMat = glm::scale(modelMat, glm::vec3(1.0f));

    auto* shader = Globals::resourceManager.getShader("model");
    shader->use();
    shader->setMat4(modelMat, "u_model");
    this->model->render(*shader, modelMat);
}
