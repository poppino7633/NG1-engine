#include <NG1/camera.hpp>

void Camera::bind(unsigned int index, State& state) { 
  state.bindCamera(ubo.getId(), index);
}
glm::mat4 Camera::getViewMatrix() { return matrices.view; }
void Camera::setViewMatrix(glm::mat4 viewMatrix) {
  matrices.view = viewMatrix;
  updateUBO();
}
glm::mat4 Camera::getProjMatrix() { return matrices.proj; }
void Camera::setProjMatrix(glm::mat4 proj) {
  matrices.proj = proj;
  updateUBO();
}

void Camera::updateUBO() { ubo.updateFirst(matrices); }

CameraPerspective::CameraPerspective(float FOV, float ratio, float nearPlane,
                                     float farPlane)
    : fov(FOV), ratio(ratio), nearPlane(nearPlane), farPlane(farPlane) {

  updateProj();
}


void CameraPerspective::bind(unsigned int index, State& state) { 
  camera.bind(index, state); 
}
glm::mat4 CameraPerspective::getViewMatrix() {
  return camera.getViewMatrix();
}
void CameraPerspective::setViewMatrix(glm::mat4 viewMatrix) {
  camera.setViewMatrix(viewMatrix);
}
void CameraPerspective::setFOV(float fov) {
  this->fov = fov;
  updateProj();
}
void CameraPerspective::setRatio(float ratio) {
  this->ratio = ratio;
  updateProj();
}
void CameraPerspective::setNearPlane(float nearPlane) {
  this->nearPlane = nearPlane;
  updateProj();
}
void CameraPerspective::setFarPlane(float farPlane) {
  this->farPlane = farPlane;
  updateProj();
}

void CameraPerspective::updateProj() {
  camera.setProjMatrix(glm::perspective(fov, ratio, nearPlane, farPlane));
}

CameraOrthographic::CameraOrthographic(glm::vec2 bottomLeft, glm::vec2 topRight,
                                       float nearPlane, float farPlane)
    : bottomLeft(bottomLeft), topRight(topRight), nearPlane(nearPlane),
      farPlane(farPlane) {
  updateProj();
}


void CameraOrthographic::bind(unsigned int index, State& state) { 
  camera.bind(index, state); 
}
glm::mat4 CameraOrthographic::getViewMatrix() {
  return camera.getViewMatrix();
}
void CameraOrthographic::setViewMatrix(glm::mat4 viewMatrix) {
  camera.setViewMatrix(viewMatrix);
}
void CameraOrthographic::setBottomLeft(glm::vec2 bottomLeft) {
  this->bottomLeft = bottomLeft;
  updateProj();
}
void CameraOrthographic::setTopRight(glm::vec2 topRight) {
  this->topRight = topRight;
  updateProj();
}
void CameraOrthographic::setNearPlane(float nearPlane) {
  this->nearPlane = nearPlane;
  updateProj();
}
void CameraOrthographic::setFarPlane(float farPlane) {
  this->farPlane = farPlane;
  updateProj();
}

void CameraOrthographic::updateProj() {
  camera.setProjMatrix(glm::ortho(bottomLeft.x, topRight.x, bottomLeft.y,
                                  topRight.y, nearPlane, farPlane));
}
