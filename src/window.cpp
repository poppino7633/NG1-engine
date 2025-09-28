#include <glad/glad.h>
#include <NG1/window.hpp>

void Window::framebuffer_size_callback(GLFWwindow *window, int width,
                                       int height) {
  Window *parentWindow = (Window *)glfwGetWindowUserPointer(window);
  parentWindow->onResize(width, height);
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void Window::onResize(unsigned int width, unsigned int height) {
  this->width = width;
  this->height = height;
}

Window::Window(const char *title, unsigned int width, unsigned int height,
               bool resizeable) {

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW!" << std::endl;
    throw;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, resizeable ? GLFW_TRUE : GLFW_FALSE);


  this->ptr = glfwCreateWindow(width, height, title, NULL, NULL);
  this->width = width;
  this->height = height;
  this->resizeable = resizeable;
  this->title = title;

  if (this->ptr == NULL) {
    std::cerr << "Failed to create GLFW window!" << std::endl;
    throw;
  }
  glfwSetWindowUserPointer(this->ptr, this);
  glfwMakeContextCurrent(this->ptr);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD!" << std::endl;
    throw;
  }
  glViewport(0, 0, width, height);

  glfwSetFramebufferSizeCallback(this->ptr, Window::framebuffer_size_callback);

  #ifdef DEBUG
  std::cerr << "Created window at " << this->ptr << std::endl;
  #endif
}

Window::~Window() {
  #ifdef DEBUG
  std::cerr << "Destroyed window at " << this->ptr << std::endl;
  #endif
  glfwDestroyWindow(this->ptr);
}

GLFWwindow *Window::getPtr() { return this->ptr; }

void Window::setTitle(const char *title) {
  glfwSetWindowTitle(this->ptr, title);
  this->title = title;
}

void Window::setSize(unsigned int width, unsigned int height) {
  if(!resizeable) return;
  glfwSetWindowSize(this->ptr, width, height);
  this->width = width;
  this->height = height;
}
std::pair<unsigned int, unsigned int> Window::getSize() {
  return {width, height};
}

bool Window::isResizable() { return resizeable; }
