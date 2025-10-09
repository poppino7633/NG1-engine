#include <NG1/shader.hpp>
#include <fstream>
#include <glad/glad.h>
#include <iostream>

std::string readFromFile(std::filesystem::path path) {
  std::ifstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  std::string code;

  try {
    file.open(path);
    std::stringstream shaderStream;
    shaderStream << file.rdbuf();
    file.close();
    code = shaderStream.str();

  } catch (std::ifstream::failure e) {
#ifdef DEBUG
    std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ " << path
              << std::endl;
#endif
    throw;
  }
  return code;
}

VertexShader::VertexShader(std::string code) {
  id = glCreateShader(GL_VERTEX_SHADER);
  const char *codePtr = code.c_str();
  glShaderSource(id, 1, &codePtr, NULL);
  glCompileShader(id);

  int success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  if (!success) {
#ifdef DEBUG
    char infoLog[512];
    glGetShaderInfoLog(id, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
#endif
    return;
  }
  std::clog << "Created vertex shader " << id << std::endl;
}

VertexShader::~VertexShader() {
  glDeleteShader(id);
#ifdef DEBUG
  std::clog << "Destroyed vertex shader " << id << std::endl;
#endif
}

unsigned int VertexShader::getId() { return id; }

FragmentShader::FragmentShader(std::string code) {
  id = glCreateShader(GL_FRAGMENT_SHADER);
  const char *codePtr = code.c_str();
  glShaderSource(id, 1, &codePtr, NULL);
  glCompileShader(id);

  int success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  if (!success) {
#ifdef DEBUG
    char infoLog[512];
    glGetShaderInfoLog(id, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
#endif
  }
  std::clog << "Created fragment shader " << id << std::endl;
}

unsigned int FragmentShader::getId() { return id; }

FragmentShader::~FragmentShader() {
  glDeleteShader(id);
#ifdef DEBUG
  std::clog << "Destroyed fragment shader " << id << std::endl;
#endif
}

ShaderProgram::ShaderProgram(VertexShader vertexShader,
                             FragmentShader fragmentShader) {
  id = glCreateProgram();
  glAttachShader(id, vertexShader.getId());
  glAttachShader(id, fragmentShader.getId());

  glLinkProgram(id);
  int success;
  glGetProgramiv(id, GL_LINK_STATUS, &success);

  if (!success) {
#ifdef DEBUG
    char infoLog[512];
    glGetProgramInfoLog(id, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
#endif
    throw;
  }
#ifdef DEBUG
  std::clog << "Created shader program " << id << std::endl;
#endif
}
unsigned int ShaderProgram::getId() { return id; }

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(id);
#ifdef DEBUG
  std::clog << "Destroyed shader program " << id << std::endl;
#endif
}
void ShaderProgram::use(State& state) {
  state.useShaderProgram(id);
}
