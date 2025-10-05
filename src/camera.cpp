#include <NG1/camera.hpp>

void Camera::updateUBO() { ubo.updateFirst(matrices); }

CameraPerspective::CameraPerspective(float FOV, float ratio, float nearPlane,
                                     float farPlane)
    : fov(FOV), ratio(ratio), nearPlane(nearPlane), farPlane(farPlane) {

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

void CameraOrthographic::updateProj() {
  camera.setProjMatrix(glm::ortho(bottomLeft.x, topRight.x, bottomLeft.y,
                                  topRight.y, nearPlane, farPlane));
}
