#include <NG1/vao.hpp>
#include <NG1/transform.hpp>

class Quad {
public:
  Quad(VAO3DInstanced& vao); 
  void draw();
  const std::vector<Transform>& getTransforms() { return transforms; }
  void setTransforms(std::vector<Transform>& transforms);
  void updateTransforms(unsigned int offset, std::vector<Transform>& transforms);
private:
  std::vector<Transform> transforms;
  VAO3DInstanced& vao;
  Buffer<Vertex3D> vbo;
  Buffer<glm::mat4> matrices;
  Buffer<unsigned int> ebo;
};
