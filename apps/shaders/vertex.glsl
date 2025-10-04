#version 460 core
layout (location = 0) in vec2 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec2 aTex; // the color variable has attribute position 1

layout(std140, binding = 5) uniform Colors {
  vec3 color; 
};
  
out vec3 ourColor; // output a color to the fragment shader

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);
    ourColor = color; // set ourColor to the input color we got from the vertex data

}       

