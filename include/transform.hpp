#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

class Transform {
public:
  Transform(); 
  Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
  glm::mat4 toMatrix();

  glm::vec3 getPosition(); 
  glm::quat getRotation();
  glm::vec3 getScale(); 

  void setPosition(glm::vec3 position);
  void setRotation(glm::quat rotation);
  void setScale(glm::vec3 scale);

  static std::vector<glm::mat4> toMatrixArray(std::vector<Transform>& transforms);
private:
  glm::vec3 position = {0.0f, 0.0f, 0.0f};
  glm::quat rotation = {1.0f, 0.0f, 0.0f, 0.0f};
  glm::vec3 scale = {1.0f, 1.0f, 1.0f};
};
