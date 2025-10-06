#include <NG1/mesh.hpp>
#include <transform.hpp>

class Quad {
public:
  Quad(VAO3DInstanced& vao); 
  void draw();
  std::vector<Transform> getTransforms();
  void setTransforms(std::vector<Transform>& transforms);
  void updateTransforms(unsigned int offset, std::vector<Transform>& transforms);
private:
  std::vector<Transform> transforms;
  Mesh mesh;
};
