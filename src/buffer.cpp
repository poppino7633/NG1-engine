#include <NG1/buffer.hpp>
#include <NG1/vertex.hpp>
#include <glad/glad.h>


unsigned int _createBuffer(size_t size, void* data) {
  unsigned int id; 
  glCreateBuffers(1, &id);

  glNamedBufferData(id, size, data, GL_STATIC_DRAW);
  return id;
}
