#include <NG1/primitives/quad.hpp>
#include <glad/glad.h>

Quad::Quad(VAO3DInstanced& vao) : vao(vao) {
  std::vector<Vertex3D> vertices = {
      {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
      {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f},  {1.0f, -1.0f}},
      {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f},  {-1.0f, -1.0f}},
      {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f},  {-1.0f, 1.0f}},
  };

  std::vector<unsigned int> indices = {0, 1, 3, 1, 2, 3};

  vbo.set(vertices);
  ebo.set(indices);
}

void Quad::draw() {
  vao.bindVBO(vbo);
  vao.bindEBO(ebo);
  vao.bindInstancedMat4(matrices);
  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, transforms.size());
}

void Quad::setTransforms(std::vector<Transform>& transforms) {
  std::vector<glm::mat4> mats(transforms.size());
  this->transforms = transforms;
  for(int i = 0; i < transforms.size(); i++) {
    mats[i] = transforms[i].toMatrix();
  }
  this->matrices.set(mats);
}
void Quad::updateTransforms(unsigned int offset, std::vector<Transform>& transforms) {
  std::vector<glm::mat4> mats(transforms.size());
  for(int i = 0; i < transforms.size(); i++) {
    mats[i] = transforms[i].toMatrix();
    this->transforms[i] = transforms[i];
  }
  this->matrices.update(offset, mats);
}
