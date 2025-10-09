#include <NG1/vao.hpp>

typedef struct {
  unsigned int count;
  unsigned int instanceCount;
  unsigned int firstIndex;
  int baseVertex;
  unsigned int baseInstance;
} DrawElementsIndirectCommand;


                            

class Mesh {
public:
  Mesh(unsigned int indexCount, unsigned int firstIndex, int baseVertex);
  unsigned int getIndexCount();
  unsigned int getFirstIndex();
  int getBaseVertex();
private:
  unsigned int indexCount;
  unsigned int firstIndex;
  int baseVertex;
};

class MeshManager {
public:
  MeshManager(std::vector<Vertex3D>& vertices, std::vector<unsigned int>& indices, unsigned int mode);
  void addDrawCommand(Mesh mesh, std::vector<glm::mat4>& instances);
  void generateIndirectBuffer(unsigned int mode = 2);
  void multiDraw(VAO3DInstanced& vao, State& state);
  void reset();

  Buffer<DrawElementsIndirectCommand>& getIndirectBuffer();
  
private:
  Buffer<Vertex3D> vbo;
  Buffer<unsigned int> ebo;
  Buffer<glm::mat4> instancedBuffer;
  Buffer<DrawElementsIndirectCommand> indirect;

  std::vector<glm::mat4> totalInstances;
  std::vector<DrawElementsIndirectCommand> drawCommands;

  unsigned int baseInstance = 0;
};

class MeshManagerBuilder {
public:
  Mesh addMesh(std::vector<Vertex3D>& vertices, std::vector<unsigned int>& indices);
  MeshManager generate(unsigned int mode = 0);
private:
  std::vector<Vertex3D> totalVertices;
  std::vector<unsigned int> totalIndices;
  int baseVertex = 0;
  unsigned int firstIndex = 0;
};
