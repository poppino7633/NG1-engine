#include <NG1/vertex.hpp>

class Quad {
public:
  Quad(); 
  void draw();
private:
  Buffer<Vertex2D> vbo;
  Buffer<unsigned int> ebo;
};
