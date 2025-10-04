#include <NG1/vao.hpp>
#include <NG1/transform.hpp>

class Quad {
public:
  Quad(VAO3D& vao); 
  void draw();
  Transform transform;
private:
  VAO3D& vao;
  Buffer<Vertex3D> vbo;
  Buffer<unsigned int> ebo;
};
