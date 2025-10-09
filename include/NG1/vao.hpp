#include <NG1/state.hpp>
#include <NG1/buffer.hpp>
#include <NG1/vertex.hpp>
#include <glm/mat4x4.hpp>

void _setupVAOInstancedMat4(unsigned int id, unsigned int attrib, unsigned int binding, unsigned int divisor = 1); 

class VAO {
public:
  VAO();
  unsigned int getId(); 
  void bind(State& state);
private:
  unsigned int id;
};

class VAO2D {
public:
  VAO2D();
  void bindVBO(Buffer<Vertex2D> vbo);
  void bindEBO(Buffer<unsigned int> ebo);
  void bind(State& state);
  unsigned int getId(); 
private:
  VAO vao;
};

class VAO3D {
public:
  VAO3D();
  void bindVBO(Buffer<Vertex3D> vbo);
  void bindEBO(Buffer<unsigned int> ebo);
  void bind(State& state);
  unsigned int getId(); 
private:
  unsigned int currentVBO = 0;
  unsigned int currentEBO = 0;
  VAO vao;
};

class VAO3DInstanced {
public:
  VAO3DInstanced(); 
  void bindVBO(Buffer<Vertex3D> vbo);
  void bindEBO(Buffer<unsigned int> ebo);
  void bindInstancedMat4(Buffer<glm::mat4> buffer);
  void bind(State& state); 
  unsigned int getId(); 
private:
  unsigned int currentInstanced = 0;
  VAO3D vao;
};
