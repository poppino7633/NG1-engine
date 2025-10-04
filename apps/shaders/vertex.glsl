#version 460 core
// Per vertex
layout (location = 0) in vec3 aPos;   
layout (location = 1) in vec3 aNormal; 
layout (location = 2) in vec2 aTex;
// Per instance
layout (location = 3) in mat4 aModel;

layout(std140, binding = 1) uniform Matrices {
  mat4 view;
  mat4 proj;
};

out VS_OUT {
  vec2 texCoords;
} vs_out;

void main()
{
  gl_Position = proj * view * aModel * vec4(aPos, 1.0);
  vs_out.texCoords = aTex;

}       

