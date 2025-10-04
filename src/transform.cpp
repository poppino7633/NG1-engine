#include <NG1/transform.hpp>

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale) {
  this->position = position;
  this->rotation = rotation;
  this->scale = scale;
}

glm::mat4 Transform::toMatrix() {
  glm::mat4 matrix = glm::mat4(1.0f);
  matrix = glm::translate(matrix, position);
  matrix = matrix * glm::mat4_cast(rotation);
  matrix = glm::scale(matrix, scale);

  return matrix;
}
