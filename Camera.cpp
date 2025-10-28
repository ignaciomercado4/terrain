#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

Camera::Camera(glm::vec3 _eye, glm::vec3 _front, glm::vec3 _up, float _FOV)
{
    eye = _eye;
    front = glm::normalize(_front);
    up = glm::normalize(_up);
    right = glm::normalize(glm::cross(front, up));
    FOV = _FOV;

    yaw = glm::degrees(atan2(front.z, front.x));
    pitch = glm::degrees(asin(front.y));
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(eye, eye + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspect) const
{
    return glm::perspective(glm::radians(FOV), aspect, 0.1f, 100.0f);
}

void Camera::moveForward(float speed)
{
    eye += speed * front;
}

void Camera::moveBackward(float speed)
{
    eye -= speed * front;
}

void Camera::moveRight(float speed)
{
    eye += speed * right;
}

void Camera::moveLeft(float speed)
{
    eye -= speed * right;
}

void Camera::addYaw(float offset)
{
    yaw += offset;
    updateCameraVectors();
}

void Camera::addPitch(float offset)
{
    pitch += offset;
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));
}
