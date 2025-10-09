#include <NG1/mesh.hpp>
#include <transform.hpp>

class Quad {
public:
  Quad(MeshManagerBuilder& meshManagerBuilder); 
  void addCommands(MeshManager& meshManager);
  std::vector<Transform> transforms;
  Mesh getMesh();
private:
  Mesh mesh;
};
