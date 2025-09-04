#include "Camera.hpp"
#include "../input/KeyHelper.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::view = glm::mat4(1.0f);
glm::vec3 Camera::location = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 Camera::direction = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Camera::up = glm::vec3(0.0f, 1.0f, 0.0f);

const float MOVE_SPEED = 3.0f;
const float ROTATION_SPEED = 1.5f;

void Camera::processMovement(double deltaTime) {
    float moveSpeed = MOVE_SPEED * deltaTime;
    double rotationSpeed = ROTATION_SPEED * deltaTime;

    if (KeyHelper::keys[GLFW_KEY_W]) {
        Camera::addLocation(moveSpeed * Camera::direction);
    }
    if (KeyHelper::keys[GLFW_KEY_S]) {
        Camera::addLocation(-moveSpeed * Camera::direction);
    }
    if (KeyHelper::keys[GLFW_KEY_A]) {
        glm::vec3 left = glm::normalize(glm::cross(Camera::up, Camera::direction));
        Camera::addLocation(moveSpeed * left);
    }
    if (KeyHelper::keys[GLFW_KEY_D]) {
        glm::vec3 right = glm::normalize(glm::cross(Camera::direction, Camera::up));
        Camera::addLocation(moveSpeed * right);
    }
    if (KeyHelper::keys[GLFW_KEY_SPACE]) {
        Camera::addLocation(moveSpeed * Camera::up);
    }
    if (KeyHelper::keys[GLFW_KEY_LEFT_SHIFT]) {
        Camera::addLocation(-moveSpeed * Camera::up);
    }

    if (KeyHelper::keys[GLFW_KEY_UP]) {
        Camera::rotatePitch(rotationSpeed);
    }
    if (KeyHelper::keys[GLFW_KEY_DOWN]) {
        Camera::rotatePitch(-rotationSpeed);
    }
    if (KeyHelper::keys[GLFW_KEY_LEFT]) {
        Camera::rotateYaw(rotationSpeed);
    }
    if (KeyHelper::keys[GLFW_KEY_RIGHT]) {
        Camera::rotateYaw(-rotationSpeed);
    }
}

void Camera::lookAt(glm::vec3 target) {
    view = glm::lookAt(
        Camera::location,
        target,
        glm::vec3(0, 1, 0)
    );
}

void Camera::setLocation(glm::vec3 location) {
    Camera::location = location;
    updateView();
}

void Camera::setRotation(glm::vec3 viewDirection) {
    Camera::direction = viewDirection;
    updateView();
}

void Camera::updateView() {
    glm::vec3 target = Camera::location + Camera::direction;

    view = glm::lookAt(
        Camera::location,
        target,
        Camera::up
    );
}

void Camera::addLocation(const glm::vec3& offset) {
    Camera::location += offset;
    updateView();
}

// up down
void Camera::rotatePitch(float angle) {
    glm::vec3 rotatedDir = glm::normalize(
        Camera::direction * cos(angle) +
        Camera::up * sin(angle)
    );
    Camera::setRotation(rotatedDir);
}

// left right
void Camera::rotateYaw(float angle) {
    glm::vec3 rotatedDir = glm::normalize(
        Camera::direction * cos(angle) +
        glm::cross(Camera::up, Camera::direction) * sin(angle)
    );
    Camera::setRotation(rotatedDir);
}