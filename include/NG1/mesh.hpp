#include <NG1/vao.hpp>

class Mesh {
public:
  Mesh();
  Mesh(VAO3DInstanced& vao, std::vector<Vertex3D>& vertices, std::vector<unsigned int>& indices, glm::mat4 baseModelMatrix = glm::mat4(1.0f));
  void setBaseModelMatrix(glm::mat4 baseModelMatrix);
  void setModelMatrices(std::vector<glm::mat4>& modelMatrices);
  void updateModelMatrices(unsigned int offset, std::vector<glm::mat4>& modelMatrices);
  void draw();
private:
  unsigned int count = 0;
  VAO3DInstanced& vao;
  Buffer<Vertex3D> vbo;
  Buffer<unsigned int> ebo;
  Buffer<glm::mat4> baseModelMatrixBuffer{glm::mat4(1.0f)};
  Buffer<glm::mat4> modelMatricesBuffer;

};
