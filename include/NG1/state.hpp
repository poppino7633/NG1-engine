#pragma once

class State {
public:
  void bindVAO(unsigned int VAOId);
  void useShaderProgram(unsigned int shaderProgramId);
  void bindCamera(unsigned int cameraUBOId, unsigned int index);
  void bindIndirect(unsigned int indirectId);

private:
  unsigned int currentVAO = 0;
  unsigned int currentShaderProgram = 0;
  unsigned int currentCamera = 0;
  unsigned int currentIndirect = 0;
};
