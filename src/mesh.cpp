#include <NG1/mesh.hpp>
#include <glad/glad.h>
#include <iostream>

Mesh::Mesh(unsigned int indexCount, unsigned int firstIndex, int baseVertex)
    : indexCount(indexCount), firstIndex(firstIndex), baseVertex(baseVertex) {}

unsigned int Mesh::getIndexCount() { return indexCount; }
unsigned int Mesh::getFirstIndex() { return firstIndex; }
int Mesh::getBaseVertex() { return baseVertex; }

MeshManager::MeshManager(std::vector<Vertex3D> &vertices,
                         std::vector<unsigned int> &indices,
                         unsigned int mode) {
  switch (mode) {
  case 0:
    vbo.setStatic(vertices);
    ebo.setStatic(indices);
    break;
  case 1:
    vbo.setDynamic(vertices);
    ebo.setDynamic(indices);
    break;
  case 2:
    throw;
  default:
    throw;
  }
}

void MeshManager::addDrawCommand(Mesh& mesh, std::vector<glm::mat4> &instances) {
  DrawElementsIndirectCommand command = {
      mesh.getIndexCount(), (unsigned int)instances.size(),
      mesh.getFirstIndex(), mesh.getBaseVertex(), baseInstance};
  mesh.setBaseInstance(baseInstance);
  totalInstances.insert(totalInstances.end(), instances.begin(),
                        instances.end());
  baseInstance += instances.size();
  drawCommands.push_back(command);
}
void MeshManager::generateBuffers(unsigned int mode) {
  switch (mode) {
  case 0:
    indirect.setStatic(drawCommands);
    break;
  case 1:
    indirect.setDynamic(drawCommands);
    break;
  case 2:
    indirect.setStream(drawCommands);
    break;
  default:
    throw;
  }
  instancedBuffer.setDynamic(totalInstances);
}
void MeshManager::multiDraw(VAO3DInstanced &vao, State &state) {
  vao.bind(state);
  vao.bindVBO(vbo);
  vao.bindEBO(ebo);
  vao.bindInstancedMat4(instancedBuffer);
  indirect.bindIndirect(state);
  glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, (void *)0,
                              indirect.getCount(),
                              sizeof(DrawElementsIndirectCommand));
}
void MeshManager::reset() {
  baseInstance = 0;
  totalInstances.clear();
  indirect.clear();
  instancedBuffer.clear();
  drawCommands.clear();
}
void MeshManager::updateInstancedBuffer(unsigned int offset, std::vector<glm::mat4>& instances) {
  for(unsigned int i = 0; i < instances.size(); i++) {
    totalInstances[offset+i] = instances[i];
  }
  instancedBuffer.update(offset, instances);
}
Buffer<DrawElementsIndirectCommand> &MeshManager::getIndirectBuffer() {
  return indirect;
}

Mesh MeshManagerBuilder::addMesh(std::vector<Vertex3D> &vertices,
                                 std::vector<unsigned int> &indices) {
  totalVertices.insert(totalVertices.end(), vertices.begin(), vertices.end());
  totalIndices.insert(totalIndices.end(), indices.begin(), indices.end());

  Mesh mesh(indices.size(), firstIndex, baseVertex);
  baseVertex += vertices.size();
  firstIndex += indices.size();
  return mesh;
}
MeshManager MeshManagerBuilder::generate(unsigned int mode) {
  return MeshManager(totalVertices, totalIndices, mode);
}
unsigned int Mesh::getBaseInstance() {
  return baseInstance;
}
void Mesh::setBaseInstance(unsigned int baseInstance) {
  this->baseInstance = baseInstance;
}

