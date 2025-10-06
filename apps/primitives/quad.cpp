#include <glad/glad.h>
#include <primitives/quad.hpp>

std::vector<Vertex3D> vertices = {
    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, -1.0f}},
    {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {-1.0f, -1.0f}},
    {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {-1.0f, 1.0f}},
};

std::vector<unsigned int> indices = {0, 1, 3, 1, 2, 3};

Quad::Quad(VAO3DInstanced &vao)
    : mesh(vao, vertices, indices, glm::mat4(1.0f)) {}

std::vector<Transform> Quad::getTransforms() { return transforms; }
void Quad::setTransforms(std::vector<Transform> &transforms) {
  this->transforms = transforms;
  std::vector<glm::mat4> matrices = Transform::toMatrixArray(transforms);
  mesh.setModelMatrices(matrices);
}
void Quad::updateTransforms(unsigned int offset,
                            std::vector<Transform> &transforms) {
  for (unsigned int i = 0; i < transforms.size(); i++) {
    this->transforms[offset + i] = transforms[i];
  }
  std::vector<glm::mat4> matrices = Transform::toMatrixArray(transforms);
  mesh.updateModelMatrices(offset, matrices);
}


void Quad::draw() {
  mesh.draw();
}

