#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
public:
    static glm::mat4 view;
    static glm::vec3 location;
    static glm::vec3 direction;
    static glm::vec3 up;
    
    static void lookAt(glm::vec3 target);
    static void setLocation(glm::vec3 location);
    static void setRotation(glm::vec3 viewDirection);
    static void updateView();
    
    static void addLocation(const glm::vec3& offset);

    static void rotatePitch(float angle);
    static void rotateYaw(float angle);

    static void processMovement(double deltaTime);
};
