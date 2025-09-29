#include <NG1/buffer.hpp>
#include <NG1/vertex.hpp>

class VAO {
public:
  unsigned int getId() { return id; }
protected:
  unsigned int id;
};

class VAO2D : public VAO {
public:
  VAO2D();
  void bindVBO(Buffer<Vertex2D> vbo);
  void bindEBO(Buffer<unsigned int> ebo);
  void bind();
private:
};

