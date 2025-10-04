#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


struct Vertex2D {
  glm::vec2 position;
  glm::vec2 uv;
};

struct Vertex3D {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 uv;
};

struct VertexMaterial3D {
  glm::vec3 position;
  glm::vec2 uv;
};
