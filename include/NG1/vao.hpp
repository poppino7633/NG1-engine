#include <NG1/buffer.hpp>
#include <NG1/vertex.hpp>
#include <glm/mat4x4.hpp>

void _setupVAOInstancedMat4(unsigned int id, unsigned int attrib, unsigned int binding, unsigned int divisor = 1); 

class VAO {
public:
  VAO();
  unsigned int getId() { return id; }
  void bind();
private:
  unsigned int id;
};

class VAO2D {
public:
  VAO2D();
  void bindVBO(Buffer<Vertex2D> vbo);
  void bindEBO(Buffer<unsigned int> ebo);
  void bind();
private:
  VAO vao;
};

class VAO3D {
public:
  VAO3D();
  void bindVBO(Buffer<Vertex3D> vbo);
  void bindEBO(Buffer<unsigned int> ebo);
  void bind();
  unsigned int getId() { return vao.getId(); }
private:
  VAO vao;
};

class VAO3DInstanced {
public:
  VAO3DInstanced() : vao(VAO3D()) { _setupVAOInstancedMat4(vao.getId(), 3, 1); };
  void bindVBO(Buffer<Vertex3D> vbo) { vao.bindVBO(vbo); }
  void bindEBO(Buffer<unsigned int> ebo) { vao.bindEBO(ebo); }
  void bindInstancedMat4(Buffer<glm::mat4> buffer);
  void bind() { vao.bind(); }
  unsigned int getId() { return vao.getId(); }
private:
  VAO3D vao;
};
