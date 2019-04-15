#version 300 es
precision lowp float;

in vec4 o_color;

out vec4 fragColor;

void main() {
  fragColor = o_color;
}
