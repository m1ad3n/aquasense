#version 330 core

out vec4 FragColor;
in vec4 tcolor;

void main(){
  FragColor = tcolor;
}