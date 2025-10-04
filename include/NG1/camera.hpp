#include <NG1/buffer.hpp>
#include <NG1/transform.hpp>

class Camera {
public:
  Camera(Transform transform);
  void bind(unsigned int index) { ubo.bindUniform(index); }
  Transform getTransform() { return transform; }
  void setTransform(Transform transform) {
    this->transform = transform;
    updateView();
  }
  void setProj(glm::mat4 proj) {
    matrices.proj = proj;
    updateUBO();
  }

private:
  void updateView();
  void updateUBO();
  Transform transform;
  struct Matrices {
    glm::mat4 view;
    glm::mat4 proj;
  } matrices;
  Buffer<Matrices> ubo;
};

class CameraPerspective {
public:
  CameraPerspective(float FOV, float ratio, float nearPlane, float farPlane,
                    Transform transform = {});
  void bind(unsigned int index) { camera.bind(index); }
  Transform getTransform() { return camera.getTransform(); }
  void setTransform(Transform transform) { camera.setTransform(transform); }
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
