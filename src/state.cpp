#include <NG1/state.hpp>
#include <glad/glad.h>

void State::bindVAO(unsigned int VAOId) {
  if (currentVAO == VAOId)
    return;
  currentVAO = VAOId;
  glBindVertexArray(VAOId);
}

void State::useShaderProgram(unsigned int shaderProgramId) {
  if (currentShaderProgram == shaderProgramId)
    return;
  currentShaderProgram = shaderProgramId;
  glUseProgram(shaderProgramId);
}

void State::bindCamera(unsigned int cameraUBOId, unsigned int index) {
  if (currentCamera == cameraUBOId)
    return;
  currentCamera = cameraUBOId;
  glBindBufferBase(GL_UNIFORM_BUFFER, index, cameraUBOId);
}

void State::bindIndirect(unsigned int indirectId) {
  if(currentIndirect == indirectId) return;
  currentIndirect = indirectId;
  glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectId);
}
