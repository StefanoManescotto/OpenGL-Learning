//
// Created by stefano on 14/07/26.
//

#include "../include/camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera() {}

Camera::Camera(float fov, float aspectW, float aspectH) {
    this->fov = fov;
    this->aspectW = aspectW;
    this->aspectH = aspectH;
}

Camera::~Camera() {}

void Camera::setFov(float fov) {
    if (fov >= 1.0f && fov <= 45.0f)
        this->fov = fov;
}

void Camera::setAspect(float aspectW, float aspectH) {
    if (aspectH > .0f && aspectW > .0f) {
        this->aspectW = aspectW;
        this->aspectH = aspectH;
    }
}

void Camera::setNearPlane(float nearPlane) {
    if (nearPlane >= 0.1f && nearPlane < farPlane)
        this->nearPlane = nearPlane;
}

void Camera::setFarPlane(float farPlane) {
    if (farPlane > 0.1f && nearPlane < farPlane)
        this->farPlane = farPlane;
}

void Camera::setSensitivity(float sensitivity) {
    if (sensitivity > .0f)
        this->sensitivity = sensitivity;
}

float Camera::getFov() const {
    return fov;
}

glm::vec3 Camera::getPosition() const {
    return cameraPos;
}

void Camera::moveCamera(const cameraMovement movementType, float deltaTime) {
    const float frameCameraSpeed = cameraSpeed * deltaTime;
    if (movementType == FORWARD)
        cameraPos += frameCameraSpeed * cameraFront;
    if (movementType == BACKWARD)
        cameraPos -= frameCameraSpeed * cameraFront;
    if (movementType == LEFT)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * frameCameraSpeed;
    if (movementType == RIGHT)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * frameCameraSpeed;
}

void Camera::rotateCamera(float xOffset, float yOffset) {
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if(pitch < -89.0f) {
        pitch = -89.0f;
    }

    cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront.y = sin(glm::radians(pitch));
    cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(cameraFront);
}

void Camera::updateMatrices(Shader &shader) {
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    projection = glm::perspective(glm::radians(fov), aspectW / aspectH, nearPlane, farPlane);

    shader.setMat4f("view", view);
    shader.setMat4f("projection", projection);
}
