#include <NG1/buffer.hpp>
#include <NG1/vertex.hpp>

class VAO {
public:
  VAO();
  unsigned int getId() { return id; }
  void bind();
protected:
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

