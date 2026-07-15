//
// Created by stefano on 14/07/26.
//

#ifndef GFXENGINE_CAMERA_H
#define GFXENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "shader.h"


class Camera {
private:
    float cameraSpeed = 2.5f;
    float yaw = -90.0;
    float pitch = 0.0f;
    float sensitivity = .1f;

    float fov = 45.0f;
    float aspectW = 800.0f;
    float aspectH = 600.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
public:
    enum cameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
    };

    Camera();
    Camera(float fov, float aspectW, float aspectH);
    ~Camera();

    void updateMatrices(Shader& shader);

    void setFov(float fov);
    void setAspect(float aspectW, float aspectH);
    void setNearPlane(float nearPlane);
    void setFarPlane(float farPlane);
    void setSensitivity(float sensitivity);

    float getFov() const;
    glm::vec3 getPosition() const;

    void moveCamera(cameraMovement movementType, float deltaTime);
    void rotateCamera(float xOffset, float yOffset);
};

#endif //GFXENGINE_CAMERA_H
