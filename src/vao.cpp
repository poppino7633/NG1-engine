#include <NG1/vao.hpp>
#include <glad/glad.h>

void VAO::bind() {
  glBindVertexArray(id);
}

VAO::VAO() {
  glCreateVertexArrays(1, &id);
}

VAO2D::VAO2D() {
  glEnableVertexArrayAttrib(vao.getId(), 0);
  glEnableVertexArrayAttrib(vao.getId(), 1);

  glVertexArrayAttribFormat(vao.getId(), 0, 2, GL_FLOAT, GL_FALSE,
                            offsetof(Vertex2D, position));
  glVertexArrayAttribFormat(vao.getId(), 1, 2, GL_FLOAT, GL_FALSE,
                            offsetof(Vertex2D, uv));

  glVertexArrayAttribBinding(vao.getId(), 0, 0);
  glVertexArrayAttribBinding(vao.getId(), 1, 0);
}

void VAO2D::bindVBO(Buffer<Vertex2D> vbo) {
  glVertexArrayVertexBuffer(vao.getId(), 0, vbo.getId(), 0, sizeof(Vertex2D));
}

void VAO2D::bindEBO(Buffer<unsigned int> ebo){
  glVertexArrayElementBuffer(vao.getId(), ebo.getId());
}

void VAO2D::bind() {
  vao.bind();
}


