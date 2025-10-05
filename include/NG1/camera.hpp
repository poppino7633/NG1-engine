#include <NG1/buffer.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
  void bind(unsigned int index);
  glm::mat4 getViewMatrix();
  void setViewMatrix(glm::mat4 viewMatrix);
  glm::mat4 getProjMatrix(); 
  void setProjMatrix(glm::mat4 proj); 
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
  void bind(unsigned int index); 
  glm::mat4 getViewMatrix();
  void setViewMatrix(glm::mat4 viewMatrix);  
  void setFOV(float fov);
  void setRatio(float ratio);
  void setNearPlane(float nearPlane);
  void setFarPlane(float farPlane); 
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
  CameraOrthographic(glm::vec2 bottomLeft, glm::vec2 topRight, float nearPlane, float farPlane);
  void bind(unsigned int index);
  glm::mat4 getViewMatrix();
  void setViewMatrix(glm::mat4 viewMatrix);
  void setBottomLeft(glm::vec2 bottomLeft);
  void setTopRight(glm::vec2 topRight);
  void setNearPlane(float nearPlane);
  void setFarPlane(float farPlane); 
private:
  void updateProj();

  glm::vec2 bottomLeft;
  glm::vec2 topRight;
  float nearPlane;
  float farPlane;
  Camera camera;
};
