#include <NG1/window.hpp>

class InputManager {
public:
  InputManager(Window& window);
  float getHorizontal();
  float getVertical();
  float getDepth();
  glm::vec2 getMouseDelta();
  void preUpdate();
  void postUpdate();
private:
  float horizontalAxis = 0.0f;
  float verticalAxis = 0.0f;
  float depthAxis = 0.0f;
  glm::vec2 lastCursorPos = {0.0f, 0.0f};
  Window& window;
};
