#include <NG1/mesh.hpp>
#include <glad/glad.h>

Mesh::Mesh(VAO3DInstanced& vao, std::vector<Vertex3D>& vertices, std::vector<unsigned int>& indices, glm::mat4 baseModelMatrix) : vao(vao) {
  vbo.set(vertices);
  ebo.set(indices);
  baseModelMatrixBuffer.updateFirst(baseModelMatrix);  
}

void Mesh::setBaseModelMatrix(glm::mat4 baseModelMatrix) {
  baseModelMatrixBuffer.updateFirst(baseModelMatrix); 
}
void Mesh::setModelMatrices(std::vector<glm::mat4>& modelMatrices) {
  count = modelMatrices.size();
  modelMatricesBuffer.set(modelMatrices);
}
void Mesh::updateModelMatrices(unsigned int offset, std::vector<glm::mat4>& modelMatrices) {
  modelMatricesBuffer.update(offset, modelMatrices);
}
void Mesh::draw() {
  vao.bindVBO(vbo);
  vao.bindEBO(ebo);
  vao.bindInstancedMat4(modelMatricesBuffer);
  baseModelMatrixBuffer.bindUniform(0); 

  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, count);
}

