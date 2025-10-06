#include <input.hpp>

InputManager::InputManager(Window &window) : window(window) {}

float InputManager::getHorizontal() { return horizontalAxis; }
float InputManager::getVertical() { return verticalAxis; }

float InputManager::getDepth() { return depthAxis; }
glm::vec2 InputManager::getMouseDelta() {
  return window.getCursorPos() - lastCursorPos;
}

void InputManager::preUpdate() {

  if (glfwGetKey(window.getPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window.getPtr(), true);

  horizontalAxis = 0.0f;
  if (glfwGetKey(window.getPtr(), GLFW_KEY_D) == GLFW_PRESS) {
    horizontalAxis += 1.0f;
  }
  if (glfwGetKey(window.getPtr(), GLFW_KEY_A) == GLFW_PRESS) {
    horizontalAxis -= 1.0f;
  }

  verticalAxis = 0.0f;
  if (glfwGetKey(window.getPtr(), GLFW_KEY_SPACE) == GLFW_PRESS) {
    verticalAxis += 1.0f;
  }
  if (glfwGetKey(window.getPtr(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    verticalAxis -= 1.0f;
  }

  depthAxis = 0.0f;
  if (glfwGetKey(window.getPtr(), GLFW_KEY_W) == GLFW_PRESS) {
    depthAxis += 1.0f;
  }
  if (glfwGetKey(window.getPtr(), GLFW_KEY_S) == GLFW_PRESS) {
    depthAxis -= 1.0f;
  }
}
void InputManager::postUpdate() { lastCursorPos = window.getCursorPos(); }
