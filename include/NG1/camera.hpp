#include <NG1/transform.hpp>
#include <NG1/buffer.hpp>

class Camera {
public:
  void bind(unsigned int index) {ubo.bindUniform(index);} 
private:
  struct Matrices {
    glm::mat4 view;
    glm::mat4 proj;
  } matrices;
  Buffer<Matrices> ubo;
};
