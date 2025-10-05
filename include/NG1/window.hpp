#include <utility>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window {
public:
  GLFWwindow* getPtr(); 
  std::pair<unsigned int, unsigned int> getSize();
  float getAspectRatio(); 
  bool isResizable();
  void setTitle(const char* title);
  void setSize(unsigned int width, unsigned int height);
  Window(const char* title, unsigned int width, unsigned int height, bool resizeable = 0);
  ~Window();
private:

  GLFWwindow* ptr;
  unsigned int width;
  unsigned int height;
  bool resizeable;

  const char* title;

  void onResize(unsigned int width, unsigned int height);

  static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
