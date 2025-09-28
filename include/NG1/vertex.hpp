#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <NG1/buffer.hpp>



class VAO {
public:
  unsigned int getId() { return id; }
protected:
  unsigned int id;
};

struct Vertex2D {
  glm::vec2 position;
  glm::vec2 uv;

};

template class Buffer<Vertex2D>;

class VAO2D : public VAO {
public:
  VAO2D();
  void bindVBO(Buffer<Vertex2D> vbo);
  void bindEBO(Buffer<unsigned int> ebo);
  void bind();
private:
};

