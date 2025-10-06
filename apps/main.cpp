#include <NG1/engine.hpp>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <transform.hpp>
#include <input.hpp>

void processInput(Window &window) {
  if (glfwGetKey(window.getPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window.getPtr(), true);
}

double deltaTime = 0.0f;
glm::vec3 moveKeyboard(InputManager& input, Transform transform) {
  const float moveSpeed = 1.0f;

  glm::vec3 forwardMove = transform.getForward() * input.getDepth() * moveSpeed * (float)deltaTime;
  glm::vec3 rightMove = transform.getRight() * input.getHorizontal() * moveSpeed * (float)deltaTime;
  glm::vec3 upMove = glm::vec3{0.0f, 1.0f, 0.0f} * input.getVertical() * moveSpeed * (float) deltaTime;

  return transform.getPosition() - forwardMove + rightMove + upMove;
  
}

glm::quat rotateByMouse(InputManager& input) {
  const float sensitivity = 0.02f;
  glm::vec2 delta = input.getMouseDelta() * sensitivity;

  static float pitch = 0.0f;
  static float yaw = 0.0f;

  pitch -= delta.y;
  yaw -= delta.x;

  if(pitch > 89.0f) pitch = 89.0f;
  if(pitch < -89.0f) pitch = -89.0f;

  while(yaw > 180.0f) yaw -= 360.0f;
  while(yaw < -180.0f) yaw += 360.0f;

  glm::quat rotation = {glm::vec3{pitch, yaw, 0.0f}};


  return rotation;
  
}

double lastTime = 0.0f;



int main() {
#ifdef DEBUG
  std::cerr << "Setup in debug mode" << std::endl;
#endif
  Window win("Test", 1280, 720, false);
  setup();
  InputManager input(win);

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

  
  Transform cameraTransform = {{0.0f, 0.0f, 3.0f}, glm::rotate({1.0f, 0.0f, 0.0f, 0.0f}, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)), {1.0f, 1.0f, 1.0f}};
  CameraPerspective camera(glm::radians(90.0f), win.getAspectRatio(), 0.1f, 100.0f);
  camera.setViewMatrix(cameraTransform.toMatrix());


  win.lockCursor();
  while (!glfwWindowShouldClose(win.getPtr())) {
    // input
    input.preUpdate();
    deltaTime = glfwGetTime() - lastTime;
    lastTime = glfwGetTime();

    // rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.use();
    vao.bind();

    cameraTransform.setPosition(moveKeyboard(input, cameraTransform));
    cameraTransform.setRotation(rotateByMouse(input));
    camera.setViewMatrix(glm::inverse(cameraTransform.toMatrix()));
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
    input.postUpdate();
    glfwPollEvents();
    glfwSwapBuffers(win.getPtr());
  }
  return 0;
}
