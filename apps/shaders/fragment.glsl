#version 460 core
out vec4 FragColor;  
  
in VS_OUT {
  vec2 texCoords;
} fs_in;

void main()
{
    FragColor = vec4((fs_in.texCoords + 1.0f) / 2, 1.0, 1.0);
}
