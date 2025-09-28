#include <glad/glad.h>
#include <NG1/engine.hpp>
#include <iostream>

void processInput(Window &window) {
  if (glfwGetKey(window.getPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window.getPtr(), true);
}

int main() {

  #ifdef DEBUG
  std::cerr << "Setup in debug mode" << std::endl;
  #endif
  Window win("Test", 1280, 720, false);
  setup();

  VAO2D vao;

  while (!glfwWindowShouldClose(win.getPtr())) {
    // input
    processInput(win);

    // rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // check and call events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(win.getPtr());
  }
  return 0;
}
