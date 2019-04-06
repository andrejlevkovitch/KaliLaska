# KaliLaska

Simple 2D Game Engine based on SDL2 and OpenGL ES 3 (with blackjack and hookers)

Use:
  - SDL
  - OpenGL ES 3
  - imgui
  - tinyxml
  - Tiled (for created tile maps)
  - miniz
  - base64
  - Catch2 (for testing)
  - Box2D (as physical engin)
  - gl3w
  - picopng
  - std17

Движок предназначен для создания простых 2D игр, таких как mario, bomberman и
др. В движке реализована поддержка тайловой графики, посредствам использования 
Tiled. Для описания объектов, состояний и т.д. используется xml файлы, что
обеспечит гибкость (так как ненужно перекомпилировать всю программу, а лишь
изменть загружаемый xml файл).

Перед компиляцией нужно установить:
  - sdl не ниже версии 2.0.5
  - gl3w
