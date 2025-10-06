#include <transform.hpp>

Transform::Transform() {}
Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
    : position(position), rotation(rotation), scale(scale) {}

glm::vec3 Transform::getPosition() { return position; }
glm::quat Transform::getRotation() { return rotation; }
glm::vec3 Transform::getScale() { return scale; }


glm::vec3 Transform::getForward() {
  return rotation * glm::vec3{0.0f, 0.0f, 1.0f};
}
glm::vec3 Transform::getUp(){
  return rotation * glm::vec3{0.0f, 1.0f, 0.0f};
}

glm::vec3 Transform::getRight(){
  return rotation * glm::vec3{1.0f, 0.0f, 0.0f};
}


void Transform::setPosition(glm::vec3 position) { this->position = position; }
void Transform::setRotation(glm::quat rotation) { this->rotation = rotation; }
void Transform::setScale(glm::vec3 scale) { this->scale = scale; }

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
