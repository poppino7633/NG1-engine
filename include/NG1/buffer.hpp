#include <cstdlib>
#include <vector>


unsigned int _createBuffer(size_t size, void* data); 

template <typename T> class Buffer {
public:
  Buffer(std::vector<T> &data) {
    id = _createBuffer(data.size() * sizeof(T), data.data());
    count = data.size();
  }
  unsigned int getId() { return id; }
  size_t getCount() { return count; }
  Buffer() {};

private:
  unsigned int id;
  size_t count;
};
