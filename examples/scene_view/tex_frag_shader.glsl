#version 300 es
precision lowp float;

uniform sampler2D texture0;

in vec2 o_texcoord;

out vec4 fragColor;

void main() {
  fragColor = texture(texture0, o_texcoord);
  if (fragColor.a == 0.) discard;
}
