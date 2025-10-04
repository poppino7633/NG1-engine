#pragma once
#include <cstdlib>
#include <vector>

unsigned int _createBuffer();
void _setDataStatic(unsigned int id, size_t size, void* data); 
void _updateBuffer(unsigned int id, size_t offset, size_t size, void *data);
void _bindUniformBuffer(unsigned int id, unsigned int index);
void _bindStorageBuffer(unsigned int id, unsigned int index);

template <typename T> class Buffer {
public:
  Buffer(std::vector<T> &data) {
    id = _createBuffer();
    count = data.size();
    _setdataStatic(id, data.size() * sizeof(T), data.data());
  }
  Buffer(T data) {
    id = _createBuffer();
    count = 1;
    _setDataStatic(id, sizeof(T), &data);
  }
  void set(std::vector<T> &data) {
    _setDataStatic(id, data.size() * sizeof(T), data.data());
    count = data.size();
  }
  void update(unsigned int offsetCount, std::vector<T> &data) {
    if(offsetCount + data.size() > count) throw;
    _updateBuffer(id, offsetCount * sizeof(T), data.size() * sizeof(T),
                  data.data());
  }
  void updateFirst(T data) {
    if(!count) throw;
    _updateBuffer(id, 0, sizeof(T), &data);
  }
  void bindUniform(unsigned int index) { _bindUniformBuffer(id, index); }
  void bindStorage(unsigned int index) { _bindStorageBuffer(id, index); }
  unsigned int getId() { return id; }
  size_t getCount() { return count; }
  Buffer() {
    id = _createBuffer();
    count = 0;
  };

private:
  unsigned int id;
  size_t count;
};
