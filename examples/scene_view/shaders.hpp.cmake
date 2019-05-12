// shaders.hpp
// this file was be generate automaticly by cmake

#pragma once

#include <filesystem>

const std::filesystem::path vertexShaderFile = "${CMAKE_CURRENT_SOURCE_DIR}/vertex_shader.glsl";
const std::filesystem::path fragmentShaderFile = "${CMAKE_CURRENT_SOURCE_DIR}/fragment_shader.glsl";

const std::filesystem::path vertexTexShaderFile = "${CMAKE_CURRENT_SOURCE_DIR}/tex_ver_shader.glsl";
const std::filesystem::path fragmentTexShaderFile = "${CMAKE_CURRENT_SOURCE_DIR}/tex_frag_shader.glsl";

const std::filesystem::path png = "${CMAKE_CURRENT_SOURCE_DIR}/png.png";
