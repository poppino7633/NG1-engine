#version 460 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal; // the color variable has attribute position 1
layout (location = 2) in vec2 aTex;

layout(std140, binding = 1) uniform Matrices {
  mat4 model;
  mat4 view;
  mat4 proj;
};

out VS_OUT {
  vec2 texCoords;
} vs_out;

void main()
{
  gl_Position = proj * view * model * vec4(aPos, 1.0);
  vs_out.texCoords = aTex;

}       

