#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <primitives/quad.hpp>
#include <input.hpp>
#include <NG1/engine.hpp>

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
  const float sensitivity = 0.005f;
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
  State state;

  ShaderProgram shaderProgram(
      VertexShader(readFromFile("./shaders/vertex.glsl")),
      FragmentShader(readFromFile("./shaders/fragment.glsl")));

  VAO3DInstanced vao;
  MeshManagerBuilder staticMeshesBuilder;

  Quad q(staticMeshesBuilder);
  q.transforms.resize(1000);
  for (unsigned int i = 0; i < q.transforms.size(); i++) {
    q.transforms[i].setPosition({0.3f * ((float)(i % 100 - i % 10) / 9.0f - 0.5f),
                                   3.0f * ((float)(i % 10) / 9.0f - 0.5f),
                                   -0.3f + (i%2 + i % 3 + i % 5 - 0.5) * 0.05f - (float)(i / 100) * 0.4f});
    q.transforms[i].setScale({0.15f, 0.15f, 0.15f});
  }

  Quad q2(staticMeshesBuilder);
  q2.transforms.resize(1000);
  for (unsigned int i = 0; i < q2.transforms.size(); i++) {
    q2.transforms[i].setPosition({0.3f * ((float)(i % 100 - i % 10) / 9.0f - 0.5f),
                                   3.0f * ((float)(i % 10) / 9.0f - 0.5f + 2.0f),
                                   -0.3f + (i%2 + i % 3 + i % 5 - 0.5) * 0.05f - (float)(i / 100) * 0.4f});
    q2.transforms[i].setScale({0.15f, 0.15f, 0.15f});
  }

  MeshManager staticMeshes = staticMeshesBuilder.generate();

  
  Transform cameraTransform = {{0.0f, 0.0f, 3.0f}, glm::rotate({1.0f, 0.0f, 0.0f, 0.0f}, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)), {1.0f, 1.0f, 1.0f}};
  CameraPerspective camera(glm::radians(90.0f), win.getAspectRatio(), 0.1f, 100.0f);
  camera.setViewMatrix(cameraTransform.toMatrix());

  win.lockCursor();
  glfwSwapInterval(0);


  q.addCommands(staticMeshes);
  q2.addCommands(staticMeshes);

  staticMeshes.generateBuffers();
  while (!glfwWindowShouldClose(win.getPtr())) {
    // input
    input.preUpdate();
    deltaTime = glfwGetTime() - lastTime;
    lastTime = glfwGetTime();

    // rendering commands here
    glEnable(GL_DEPTH_TEST);  
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    shaderProgram.use(state);
    camera.bind(1, state);
    cameraTransform.setPosition(moveKeyboard(input, cameraTransform));
    cameraTransform.setRotation(rotateByMouse(input));
    camera.setViewMatrix(glm::inverse(cameraTransform.toMatrix()));

    for (unsigned int i = 0; i < q.transforms.size(); i++) {
      q.transforms[i].setRotation(
          glm::angleAxis(glm::radians(90.0f) * (0.5f + i%2 + i%3 + i%5) * (float)glfwGetTime(),
                         glm::normalize(glm::vec3(1.0f * (i%2 - 0.5), 1.0f * (i%3 - 1), 0.0f))));

    }
    for (unsigned int i = 0; i < q2.transforms.size(); i++) {
      q2.transforms[i].setRotation(
          glm::angleAxis(glm::radians(90.0f) * (0.5f + i%2 + i%3 + i%5) * (float)glfwGetTime(),
                         glm::normalize(glm::vec3(1.0f * (i%2 - 0.5), 1.0f * (i%3 - 1), 0.0f))));

    }
    std::vector<glm::mat4> qMatrices = Transform::toMatrixArray(q.transforms);
    staticMeshes.updateInstancedBuffer(q.getMesh().getBaseInstance(), qMatrices);
    std::vector<glm::mat4> q2Matrices = Transform::toMatrixArray(q2.transforms);
    staticMeshes.updateInstancedBuffer(q2.getMesh().getBaseInstance(), q2Matrices);
    //std::clog << q.getMesh().getBaseInstance() << " " << q2.getMesh().getBaseInstance() << std::endl;
    /*q.addCommands(staticMeshes)*/;
    /*q2.addCommands(staticMeshes)*/;
    //std::clog << staticMeshes.getIndirectBuffer().getCount() << std::endl;
    staticMeshes.multiDraw(vao, state);
    //staticMeshes.reset();

    //q.updateTransforms(0, quadTransforms);


    // check and call events and swap the buffers
    input.postUpdate();
    glfwPollEvents();
    glfwSwapBuffers(win.getPtr());
  }
  return 0;
}
