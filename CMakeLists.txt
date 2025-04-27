cmake_minimum_required(VERSION 3.21)

message("${CMAKE_PREFIX_PATH}")

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)

project(
  bluks
  VERSION 0.0.1
  DESCRIPTION "Arcade block stacking game"
  LANGUAGES CXX)
  
find_package(battery-embed REQUIRED CONFIG)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)
find_package(VulkanHeaders REQUIRED)
  
add_executable(${PROJECT_NAME})
add_executable(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

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
)

b_embed(${PROJECT_NAME} 
src/shaders/default/default.vert.glsl
src/shaders/default/default.frag.glsl
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
  glfw
  glm::glm
  imgui::imgui
  vulkan-headers::vulkan-headers
)
