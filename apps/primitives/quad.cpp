#include <glad/glad.h>
#include <primitives/quad.hpp>

std::vector<Vertex3D> vertices = {
    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, -1.0f}},
    {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {-1.0f, -1.0f}},
    {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {-1.0f, 1.0f}},
};

std::vector<unsigned int> indices = {0, 1, 3, 1, 2, 3};


Quad::Quad(MeshManagerBuilder& meshManagerBuilder) : mesh(meshManagerBuilder.addMesh(vertices, indices)) {

}
void Quad::addCommands(MeshManager& meshManager) {
  std::vector<glm::mat4> modelMatrices = Transform::toMatrixArray(transforms);
  meshManager.addDrawCommand(mesh, modelMatrices);
}

Mesh Quad::getMesh() { return mesh; }
