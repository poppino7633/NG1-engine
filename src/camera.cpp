#include <NG1/camera.hpp>

Camera::Camera(Transform transform) : transform(transform), ubo(Matrices{}) {
  updateView();
}

void Camera::updateView() {
  matrices.view = transform.toMatrix();
  updateUBO();
}

void Camera::updateUBO() { ubo.updateFirst(matrices); }

CameraPerspective::CameraPerspective(float FOV, float ratio, float nearPlane,
                                     float farPlane, Transform transform)
    : fov(FOV), ratio(ratio), nearPlane(nearPlane), farPlane(farPlane),
      camera(transform) {

  updateProj();
}

void CameraPerspective::updateProj() {
  camera.setProj(glm::perspective(fov, ratio, nearPlane, farPlane));
}

CameraOrthographic::CameraOrthographic(glm::vec2 bottomLeft, glm::vec2 topRight,
                                       float nearPlane, float farPlane,
                                       Transform transform)
    : bottomLeft(bottomLeft), topRight(topRight), nearPlane(nearPlane),
      farPlane(farPlane), camera(transform) {
  updateProj();
}

void CameraOrthographic::updateProj() {
  camera.setProj(glm::ortho(bottomLeft.x, topRight.x, bottomLeft.y, topRight.y, nearPlane, farPlane));
}
