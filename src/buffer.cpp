#include <NG1/buffer.hpp>
#include <NG1/vertex.hpp>
#include <glad/glad.h>

void _setDataStatic(unsigned int id, size_t size, void* data) {
  glNamedBufferData(id, size, data, GL_STATIC_DRAW);
}
void _setDataDynamic(unsigned int id, size_t size, void* data){
  glNamedBufferData(id, size, data, GL_DYNAMIC_DRAW);
}
void _setDataStream(unsigned int id, size_t size, void* data){
  glNamedBufferData(id, size, data, GL_STREAM_DRAW);
}


unsigned int _createBuffer() {
  unsigned int id;
  glCreateBuffers(1, &id);

  return id;
}

void _updateBuffer(unsigned int id, size_t offset, size_t size, void *data) {
  glNamedBufferSubData(id, offset, size, data);
}

void _bindUniformBuffer(unsigned int id, unsigned int index) {
  glBindBufferBase(GL_UNIFORM_BUFFER, index, id);
}
void _bindStorageBuffer(unsigned int id, unsigned int index) {
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, id);
}

