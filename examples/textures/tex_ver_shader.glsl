#version 300 es
precision lowp float;
uniform vec2 win_size;
uniform mat3 view_mat;
uniform mat3 item_mat;

out vec2 o_texcoord;

layout(location = 0) in vec2 pos;
layout(location = 2) in vec2 texcoord;

void main() {
  mat4 to_ndc = mat4(
    2.0 / win_size.x, 0,                 0, 0,
    0,                -2.0 / win_size.y, 0, 0,
    0,                0,                 1, 0,
    -1,               1,                 0, 1
  );

  to_ndc *= mat4(view_mat);
  to_ndc *= mat4(item_mat);

  gl_Position = to_ndc * vec4(pos, 1, 1);
  o_texcoord = texcoord;
}
