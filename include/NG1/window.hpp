#pragma once
#include <utility>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class Window {
public:
  GLFWwindow *getPtr();
  std::pair<unsigned int, unsigned int> getSize();
  float getAspectRatio();
  bool isResizable();
  void setTitle(const char *title);
  void setSize(unsigned int width, unsigned int height);
  glm::vec2 getCursorPos();
  Window(const char *title, unsigned int width, unsigned int height,
         bool resizeable = 0);
  ~Window();

private:
  GLFWwindow *ptr;
  unsigned int width;
  unsigned int height;
  bool resizeable;
  glm::vec2 cursorPos;

  const char *title;

  void onResize(unsigned int width, unsigned int height);
  void onCursorPos(double xpos, double ypos);

  static void framebufferSizeCallback(GLFWwindow *window, int width,
                                        int height);
  static void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
};
