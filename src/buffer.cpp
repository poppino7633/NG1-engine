#include <NG1/buffer.hpp>
#include <glad/glad.h>

template<typename T>
Buffer<T>::Buffer(std::vector<T> &data){
  
  glCreateBuffers(1, &id);
  count = data.size();

  glNamedBufferData(id, sizeof(T) * count, data.data(), GL_STATIC_DRAW);


}

template class Buffer<unsigned int>;
