#version 300 es
uniform vec2 win_size;
uniform mat3 transform_mat;
uniform vec2 cur_pos;

uniform vec3 color;

in vec2 pos;
out vec4 outColor;

void main() {
  mat4 to_ndc = mat4(
    2.0 / win_size.x, 0,                 0, 0,
    0,                -2.0 / win_size.y, 0, 0,
    0,                0,                 1, 0,
    -1,               1,                 0, 1
  );

  gl_Position =to_ndc * vec4(transform_mat * vec3(pos + cur_pos, 1), 1);
  outColor = vec4(color, 1);
}
