#include <NG1/primitives/quad.hpp>
#include <glad/glad.h>

Quad::Quad() {
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
  
}
