#include <NG1/engine.hpp>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <transform.hpp>

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

  ShaderProgram shaderProgram(
      VertexShader(readFromFile("./shaders/vertex.glsl")),
      FragmentShader(readFromFile("./shaders/fragment.glsl")));

  VAO3DInstanced vao;

  Quad q(vao);
  std::vector<Transform> quadTransforms(200);
  std::vector<glm::mat4> quadMatrices(quadTransforms.size());
  for (int i = 0; i < quadTransforms.size(); i++) {
    quadTransforms[i].setPosition({2.0f * ((float)(i / 10) / 9.0f - 0.5f),
                                   2.0f * ((float)(i % 10) / 9.0f - 0.5f),
                                   -0.3f});
    quadTransforms[i].setScale({0.15f, 0.15f, 0.15f});
  }
  quadMatrices = Transform::toMatrixArray(quadTransforms);
  q.setModelMatrices(quadMatrices);

  
  Transform cameraTransform = {{1.0f, 0.0f, -3.0f}, glm::rotate({1.0f, 0.0f, 0.0f, 0.0f}, glm::radians(160.0f), glm::vec3(0.0f, 1.0f, 0.0f)), {1.0f, 1.0f, 1.0f}};
  CameraPerspective camera(glm::radians(90.0f), win.getAspectRatio(), 0.1f, 100.0f);
  camera.setViewMatrix(cameraTransform.toMatrix());


  while (!glfwWindowShouldClose(win.getPtr())) {
    // input
    processInput(win);

    // rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.use();
    vao.bind();

    camera.setViewMatrix(cameraTransform.toMatrix());
    camera.bind(1);

    for (int i = 0; i < quadTransforms.size(); i++) {
      quadTransforms[i].setRotation(
          glm::angleAxis(glm::radians(90.0f) * (float)glfwGetTime(),
                         glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f))));

    }

    quadMatrices = Transform::toMatrixArray(quadTransforms);
    q.updateModelMatrices(0, quadMatrices);
    q.draw();



    // check and call events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(win.getPtr());
  }
  return 0;
}
