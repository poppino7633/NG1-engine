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
  vao.bindInstancedMat4(modelMatricesBuffer);
  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, modelMatrices.size());
}


void Quad::setModelMatrices(std::vector<glm::mat4>& matrices) {
  this->modelMatrices = matrices;
  modelMatricesBuffer.set(matrices);
}
void Quad::updateModelMatrices(unsigned int offset, std::vector<glm::mat4>& matrices) {
  for(int i = 0; i < matrices.size(); i++) {
    this->modelMatrices[offset + i] = matrices[i];
  }
  modelMatricesBuffer.update(offset, matrices);
}



