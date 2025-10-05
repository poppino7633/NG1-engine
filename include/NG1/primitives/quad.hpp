#include <NG1/vao.hpp>

class Quad {
public:
  Quad(VAO3DInstanced& vao); 
  void draw();
  const std::vector<glm::mat4> getModelMatrices(); 
  void setModelMatrices(std::vector<glm::mat4>& matrices);
  void updateModelMatrices(unsigned int offset, std::vector<glm::mat4>& matrices);
private:
  std::vector<glm::mat4> modelMatrices;
  VAO3DInstanced& vao;
  Buffer<Vertex3D> vbo;
  Buffer<glm::mat4> modelMatricesBuffer;
  Buffer<unsigned int> ebo;
};
