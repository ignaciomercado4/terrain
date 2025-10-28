#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    glm::vec3 eye, up, right, front;
    float yaw, pitch;
    float FOV;

public:
    Camera(glm::vec3 _eye = glm::vec3(0.0f, 1.0f, 3.0f),
           glm::vec3 _front = glm::vec3(0.0f, 0.0f, -1.0f),
           glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f),
           float _FOV = 80.0f);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspect = 1.0f) const;
    glm::vec3 getEye() const { return eye; }

    void moveForward(float speed);
    void moveBackward(float speed);
    void moveRight(float speed);
    void moveLeft(float speed);

    void addYaw(float offset);
    void addPitch(float offset);

private:
    void updateCameraVectors();
};

#endif
