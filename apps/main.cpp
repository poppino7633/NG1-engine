#include <NG1/engine.hpp>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <iostream>

void processInput(Window &window) {
  if (glfwGetKey(window.getPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window.getPtr(), true);
}

struct Matrices {
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 proj;
} matrices;

struct Colors {
  glm::vec3 color;
} colors;

int main() {

#ifdef DEBUG
  std::cerr << "Setup in debug mode" << std::endl;
#endif
  Window win("Test", 1280, 720, false);
  setup();

  VAO2D vao;
  Quad q(vao);

  ShaderProgram shaderProgram(
      VertexShader(readFromFile("./shaders/vertex.glsl")),
      FragmentShader(readFromFile("./shaders/fragment.glsl")));

  Buffer<Colors> ubo(Colors{});
  colors.color = {0.7f, 0.4f, 0.5f};

  while (!glfwWindowShouldClose(win.getPtr())) {
    // input
    processInput(win);

    // rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.use();
    ubo.updateFirst(colors);
    ubo.bindUniform(5);

    vao.bind();
    q.draw();

    // check and call events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(win.getPtr());
  }
  return 0;
}
