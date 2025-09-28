#include <bits/stdc++.h>

template <typename T> class Buffer {
public:
  Buffer(std::vector<T> &data);
  unsigned int getId() { return id; }
  size_t getCount() { return count; }
  Buffer() {};

private:
  unsigned int id;
  size_t count;
};

