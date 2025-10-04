#include <NG1/engine.hpp>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
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

int main() {

#ifdef DEBUG
  std::cerr << "Setup in debug mode" << std::endl;
#endif
  Window win("Test", 1280, 720, false);
  setup();

  ShaderProgram shaderProgram(
      VertexShader(readFromFile("./shaders/vertex.glsl")),
      FragmentShader(readFromFile("./shaders/fragment.glsl")));

  VAO3D vao;
  Quad q(vao);

  q.transform.setPosition({0.0f, 0.0f, -3.0f});


  Transform cameraTransform({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});

  matrices.proj =
      glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);
  std::cout << glm::to_string(q.transform.toMatrix() * glm::vec4({0.5f, 0.5f, 0.0f, 1.0f})) << std::endl;



  Buffer<Matrices> ubo(Matrices{});

  while (!glfwWindowShouldClose(win.getPtr())) {
    // input
    processInput(win);

    // rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.use();
    vao.bind();

    q.transform.setRotation(glm::angleAxis(glm::radians(60.0f) * (float)glfwGetTime(), glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f))));
    matrices.model = q.transform.toMatrix();
    matrices.view = cameraTransform.toMatrix();
    ubo.updateFirst(matrices);
    ubo.bindUniform(1);


    q.draw();

    // check and call events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(win.getPtr());
  }
  return 0;
}
