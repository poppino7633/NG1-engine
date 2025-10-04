#include <NG1/camera.hpp>

Camera::Camera(Transform transform) : transform(transform), ubo(Matrices{}) { updateView(); }

void Camera::updateView() { 
  matrices.view = transform.toMatrix(); 
  updateUBO();
}


void Camera::updateUBO() {
  ubo.updateFirst(matrices);
}

CameraPerspective::CameraPerspective(float FOV, float ratio, float nearPlane,
                                     float farPlane, Transform transform)
    : fov(FOV), ratio(ratio), nearPlane(nearPlane), farPlane(farPlane),
      camera(transform) {

  updateProj();
}

void CameraPerspective::updateProj() {
  camera.setProj(glm::perspective(fov, ratio, nearPlane, farPlane));
}
