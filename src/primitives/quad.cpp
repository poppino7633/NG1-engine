#include <NG1/primitives/quad.hpp>
#include <glad/glad.h>

Quad::Quad(VAO2D& vao) : vao(vao) {
  std::vector<Vertex2D> vertices = {
      {{0.5f, 0.5f}, {1.0f, 1.0f}},
      {{0.5f, -0.5f}, {1.0f, -1.0f}},
      {{-0.5f, -0.5f}, {-1.0f, -1.0f}},
      {{-0.5f, 0.5f}, {-1.0f, 1.0f}},
  };

  std::vector<unsigned int> indices = {0, 1, 3, 1, 2, 3};

  vbo = Buffer<Vertex2D>(vertices);
  ebo = Buffer<unsigned int>(indices);
}

void Quad::draw() {
  vao.bindVBO(vbo);
  vao.bindEBO(ebo);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);  
}
