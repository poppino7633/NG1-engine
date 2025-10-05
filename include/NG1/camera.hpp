#include <NG1/buffer.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
  void bind(unsigned int index) { ubo.bindUniform(index); }
  glm::mat4 getViewMatrix() { return matrices.view; }
  void setViewMatrix(glm::mat4 viewMatrix) {
    matrices.view = viewMatrix;
    updateUBO();
  }
  glm::mat4 getProjMatrix() { return matrices.proj; }
  void setProjMatrix(glm::mat4 proj) {
    matrices.proj = proj;
    updateUBO();
  }

private:
  void updateUBO();
  struct Matrices {
    glm::mat4 view;
    glm::mat4 proj;
  } matrices;
  Buffer<Matrices> ubo = {Matrices{}};
};

class CameraPerspective {
public:
  CameraPerspective(float FOV, float ratio, float nearPlane, float farPlane);
  void bind(unsigned int index) { camera.bind(index); }
  glm::mat4 getViewMatrix() {
    return camera.getViewMatrix();
  }
  void setViewMatrix(glm::mat4 viewMatrix) {
    camera.setViewMatrix(viewMatrix);
  }
  void setFOV(float fov) {
    this->fov = fov;
    updateProj();
  }
  void setRatio(float ratio) {
    this->ratio = ratio;
    updateProj();
  }
  void setNearPlane(float nearPlane) {
    this->nearPlane = nearPlane;
    updateProj();
  }
  void setFarPlane(float farPlane) {
    this->farPlane = farPlane;
    updateProj();
  }

private:
  void updateProj();

  float fov;
  float ratio;
  float nearPlane;
  float farPlane;
  Camera camera;
};

class CameraOrthographic {
public:
  CameraOrthographic(glm::vec2 bottomLeft, glm::vec2 topRight, float nearPlane,
                     float farPlane);
  void bind(unsigned int index) { camera.bind(index); }
  glm::mat4 getViewMatrix() {
    return camera.getViewMatrix();
  }
  void setViewMatrix(glm::mat4 viewMatrix) {
    camera.setViewMatrix(viewMatrix);
  }
  void setBottomLeft(glm::vec2 bottomLeft) {
    this->bottomLeft = bottomLeft;
    updateProj();
  }
  void setTopRight(glm::vec2 topRight) {
    this->topRight = topRight;
    updateProj();
  }
  void setNearPlane(float nearPlane) {
    this->nearPlane = nearPlane;
    updateProj();
  }
  void setFarPlane(float farPlane) {
    this->farPlane = farPlane;
    updateProj();
  }

private:
  void updateProj();

  glm::vec2 bottomLeft;
  glm::vec2 topRight;
  float nearPlane;
  float farPlane;
  Camera camera;
};
