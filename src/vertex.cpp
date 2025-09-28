#include <NG1/vertex.hpp>
#include <glad/glad.h>

VAO2D::VAO2D() {
  glCreateVertexArrays(1, &id);
  glEnableVertexArrayAttrib(id, 0);
  glEnableVertexArrayAttrib(id, 1);

  glVertexArrayAttribFormat(id, 0, 2, GL_FLOAT, GL_FALSE,
                            offsetof(Vertex2D, position));
  glVertexArrayAttribFormat(id, 1, 2, GL_FLOAT, GL_FALSE,
                            offsetof(Vertex2D, uv));

  glVertexArrayAttribBinding(id, 0, 0);
  glVertexArrayAttribBinding(id, 1, 0);
}

void VAO2D::bindVBO(Buffer<Vertex2D> vbo) {
  glVertexArrayVertexBuffer(id, 0, vbo.getId(), 0, sizeof(Vertex2D));
}

void VAO2D::bindEBO(Buffer<unsigned int> ebo){
  glVertexArrayElementBuffer(id, ebo.getId());
}

void VAO2D::bind() {
  glBindVertexArray(id);
}
