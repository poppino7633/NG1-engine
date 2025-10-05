#include <transform.hpp>

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
    : position(position), rotation(rotation), scale(scale) {}

glm::mat4 Transform::toMatrix() {
  glm::mat4 matrix = glm::mat4(1.0f);
  matrix = glm::translate(matrix, position);
  matrix = matrix * glm::mat4_cast(rotation);
  matrix = glm::scale(matrix, scale);

  return matrix;
}


std::vector<glm::mat4> Transform::toMatrixArray(std::vector<Transform>& transforms) {
  std::vector<glm::mat4> matrices(transforms.size());
  for(int i = 0; i < matrices.size(); i++) {
    matrices[i] = transforms[i].toMatrix();
  }
  return matrices;
}
