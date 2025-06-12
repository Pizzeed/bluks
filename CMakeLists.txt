cmake_minimum_required(VERSION 3.21)

message("${CMAKE_PREFIX_PATH}")

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  bluks
  VERSION 0.0.1
  DESCRIPTION "Arcade block stacking game"
  LANGUAGES CXX)

find_package(battery-embed REQUIRED CONFIG)
find_package(stb REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL)

add_executable(${PROJECT_NAME})
add_executable(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

include_directories( ${OPENGL_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME}
PUBLIC
PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/
)

target_sources(${PROJECT_NAME}
PUBLIC
PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/main.cc

  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/utils/color.cc

  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/game_base/map/map.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/game_base/bluks_game/bluks_game.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/game_base/shapes/shape.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/game_base/shapes/shape_factory.cc
  
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/application/graphics/glad/glad.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/application/graphics/shaders/shader_program/shader_program.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/application/graphics/shaders/shader_manager/shader_manager.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/application/graphics/text/text_render.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/application/graphics/text/font.cc

  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/application/application.cc

  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/application/input/input_handler.cc

)

b_embed(${PROJECT_NAME}
  src/shaders/default/default.vert.glsl
)
b_embed(${PROJECT_NAME}
  src/shaders/default/default.frag.glsl
)
b_embed(${PROJECT_NAME}
  src/shaders/simple_texture/simple_texture.vert.glsl
)
b_embed(${PROJECT_NAME}
  src/shaders/simple_texture/simple_texture.frag.glsl
)
b_embed(${PROJECT_NAME}
  resources/fonts/roboto.ttf
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
  ${OPENGL_LIBRARIES}
  stb::stb
  glfw
  glm::glm
)
