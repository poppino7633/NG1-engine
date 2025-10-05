#include <NG1/vao.hpp>
#include <glad/glad.h>

void _setupVAOInstancedMat4(unsigned int id, unsigned int attrib,
                            unsigned int binding, unsigned int divisor) {

  for (int i = 0; i < 4; i++) {
    glEnableVertexArrayAttrib(id, attrib + i);
    glVertexArrayAttribFormat(id, attrib + i, 4, GL_FLOAT, GL_FALSE,
                              i * sizeof(glm::vec4));
    glVertexArrayAttribBinding(id, attrib + i, binding);
  }

  glVertexArrayBindingDivisor(id, binding, divisor);
}

VAO::VAO() { glCreateVertexArrays(1, &id); }

unsigned int VAO::getId() { return id; }
void VAO::bind() { glBindVertexArray(id); }

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

void VAO2D::bindEBO(Buffer<unsigned int> ebo) {
  glVertexArrayElementBuffer(vao.getId(), ebo.getId());
}

void VAO2D::bind() { vao.bind(); }

unsigned int VAO2D::getId() { return vao.getId(); }

VAO3D::VAO3D() : vao(VAO()) {

  glEnableVertexArrayAttrib(vao.getId(), 0);
  glEnableVertexArrayAttrib(vao.getId(), 1);
  glEnableVertexArrayAttrib(vao.getId(), 2);

  glVertexArrayAttribFormat(vao.getId(), 0, 3, GL_FLOAT, GL_FALSE,
                            offsetof(Vertex3D, position));
  glVertexArrayAttribFormat(vao.getId(), 1, 3, GL_FLOAT, GL_FALSE,
                            offsetof(Vertex3D, normal));
  glVertexArrayAttribFormat(vao.getId(), 2, 2, GL_FLOAT, GL_FALSE,
                            offsetof(Vertex3D, uv));

  glVertexArrayAttribBinding(vao.getId(), 0, 0);
  glVertexArrayAttribBinding(vao.getId(), 1, 0);
  glVertexArrayAttribBinding(vao.getId(), 2, 0);
}

void VAO3D::bindVBO(Buffer<Vertex3D> vbo) {
  glVertexArrayVertexBuffer(vao.getId(), 0, vbo.getId(), 0, sizeof(Vertex3D));
}

void VAO3D::bindEBO(Buffer<unsigned int> ebo) {
  glVertexArrayElementBuffer(vao.getId(), ebo.getId());
}

void VAO3D::bind() { vao.bind(); }

unsigned int VAO3D::getId() { return vao.getId(); }

VAO3DInstanced::VAO3DInstanced() : vao(VAO3D()) {
  _setupVAOInstancedMat4(vao.getId(), 3, 1);
}
void VAO3DInstanced::bindVBO(Buffer<Vertex3D> vbo) { 
  vao.bindVBO(vbo); 
}
void VAO3DInstanced::bindEBO(Buffer<unsigned int> ebo) { 
  vao.bindEBO(ebo); 
}
void VAO3DInstanced::bind() { 
  vao.bind(); 
}
void VAO3DInstanced::bindInstancedMat4(Buffer<glm::mat4> buffer) {
  glVertexArrayVertexBuffer(vao.getId(), 1, buffer.getId(), 0,
                            sizeof(glm::mat4));
}

unsigned int VAO3DInstanced::getId() { return vao.getId(); }
