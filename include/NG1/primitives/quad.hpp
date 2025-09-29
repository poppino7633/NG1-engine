#include <NG1/vao.hpp>

class Quad {
public:
  Quad(VAO2D& vao); 
  void draw();
private:
  VAO2D& vao;
  Buffer<Vertex2D> vbo;
  Buffer<unsigned int> ebo;
};
