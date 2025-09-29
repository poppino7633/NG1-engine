#include <string>
#include <filesystem>


std::string readFromFile(std::filesystem::path path); 


class VertexShader {
public:
  unsigned int getId() { return id; }
  VertexShader(std::string code);
  ~VertexShader();
private:
  unsigned int id;
};

class FragmentShader {
public:
  unsigned int getId() { return id; }
  FragmentShader(std::string code);
  ~FragmentShader();
private:
  unsigned int id;
};

class ShaderProgram {
public:
  unsigned int getId() { return id; }
  ShaderProgram(VertexShader vertexShader, FragmentShader fragmentShader);
  ~ShaderProgram();

  void use();
private:
  unsigned int id;
};
