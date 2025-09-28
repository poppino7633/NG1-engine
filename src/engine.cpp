#include <NG1/engine.hpp>

void test() {
  std::cout << "Test even more successful!" << std::endl;
}

void error_callback( int error, const char *msg ) {
    std::string s;
    s = " [" + std::to_string(error) + "] " + msg + '\n';
    std::cerr << s << std::endl;
}

void setup() {
  glfwSetErrorCallback((GLFWerrorfun)error_callback);
}


