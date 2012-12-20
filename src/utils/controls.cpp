#include "controls.h"

// old control system, not used, leaved for future generations ;_;

using namespace glm;

int screenHeight;
int screenWidth;

void initInput() {
    GLFWvidmode vid;
    glfwGetDesktopMode(&vid);
    screenHeight = vid.Height;
    screenWidth = vid.Width;
}

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::vec3 position = glm::vec3(0, 0, 5);
glm::vec3 direction;

glm::mat4 getViewMatrix() {
    return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
    return ProjectionMatrix;
}
glm::vec3 getPosition() {
    return position;
}
glm::vec3 getDirection() {
    return direction;
}

float horizontalAngle = 0.f;
float verticalAngle = 1.f;

float initialFoV = 45.0f;

float speed = 3.0f;
float mouseSpeed = 0.005f;

bool lockMouse = true;

void computeMatricesFromInputs() {

    static double lastTime = glfwGetTime();

    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    int xpos, ypos;
    glfwGetMousePos(&xpos, &ypos);

    if (lockMouse) {
        glfwSetMousePos(200, 200);

        horizontalAngle += mouseSpeed * float(200 - xpos);
        verticalAngle += mouseSpeed * float(200 - ypos);
        if (verticalAngle < -2.f)
            verticalAngle = -2.f;
        if (verticalAngle > 2.f)
            verticalAngle = 2.f;
    }
    direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));

    glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0,
            cos(horizontalAngle - 3.14f / 2.0f));

    glm::vec3 up = glm::cross(right, direction);

    speed = 3.0f;
    if (glfwGetKey(GLFW_KEY_LSHIFT) == GLFW_PRESS) {
        speed = 7.0f;
    }
    if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(87) == GLFW_PRESS) {
        position += direction * deltaTime * speed;
    }
    if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(83) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(68) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }
    if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(65) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }
    if (glfwGetKey(GLFW_KEY_TAB) == GLFW_PRESS)
        lockMouse = !lockMouse;
    float FoV = initialFoV - 5 * glfwGetMouseWheel();

    ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
    ViewMatrix = glm::lookAt(position, position + direction, up);

    lastTime = currentTime;
}
