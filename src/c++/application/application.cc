#include <iostream>
#include <chrono>

#include <battery/embed.hpp>
#include <application/graphics/glad/glad.h>
#include <GLFW/glfw3.h>

#include <utils/color.h>
#include <game_base/shapes/block.h>
#include <application/input/input_handler.h>
#include <application/application.h>

namespace bluks::app
{
  auto Application::framebuffer_size_callback(
    GLFWwindow* window,
    int width,
    int height
  ) -> void
  {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window
    ));
    app->m_window_width = width;
    app->m_window_height = height;
    glViewport(0, 0, width, height);
  }

  auto Application::get() -> Application*
  {
    static Application inst;
    return &inst;
  }

  Application::Application()
    : m_game()
  {
    init_graphics();
    m_input_handler = std::make_unique<input::InputHandler>(m_window);

    m_input_handler
      ->bind_to_action(input::InputHandler::Action::Down, [this]() {
        if(m_game.ongoing())
          m_game.tick();
      });

    m_input_handler
      ->bind_to_action(input::InputHandler::Action::Left, [this]() {
        if(m_game.ongoing())
          m_game.current_shape().move_left();
      });
    m_input_handler
      ->bind_to_action(input::InputHandler::Action::Right, [this]() {
        if(m_game.ongoing())
          m_game.current_shape().move_right();
      });

    m_input_handler
      ->bind_to_action(input::InputHandler::Action::Drop, [this]() {
        if(m_game.ongoing()) {
          m_game.current_shape().drop();
          m_game.check_lines();
          m_game.spawn_new_shape();
        }
      });
    m_input_handler->bind_to_action(input::InputHandler::Action::Up, [this]() {
      if(m_game.ongoing()) {
        m_game.current_shape().rotate_clockwise();
      }
    });

    m_game.start();
  }

  Application::~Application() { cleanup(); }

  auto Application::init_graphics() -> void
  {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(
      m_window_width,
      m_window_height,
      "Bluks",
      nullptr,
      nullptr
    );
    if(not m_window) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return;
    }
    glfwMakeContextCurrent(m_window);
    if(! gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      glfwTerminate();
      return;
    }
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(
      m_window,
      &Application::framebuffer_size_callback
    );
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(
      1,
      3,
      GL_FLOAT,
      GL_FALSE,
      6 * sizeof(f32),
      (void*)(3 * sizeof(f32))
    );
    glEnableVertexAttribArray(1);
    m_shader_manager = std::make_unique<graphics::shaders::ShaderManager>();
  }

  auto Application::run_graphics_loop() -> void
  {
    using Action = input::InputHandler::Action;
    using namespace std::chrono;

    auto last_time = steady_clock::now();

    while(! glfwWindowShouldClose(m_window)) {
      auto current_time = steady_clock::now();
      auto elapsed = duration_cast<seconds>(current_time - last_time);

      if(elapsed.count() >= m_game.tick_period()) {
        m_game.tick();
        last_time = current_time;
      }
      glfwPollEvents();
      m_input_handler->process_keys();

      auto vertices = std::vector<f32>();
      auto indices = std::vector<u32>();
      auto map_verts = get_gl_map_background_vertices();
      auto map_inds = std::vector<u32> {0, 1, 3, 1, 2, 3};
      vertices.insert(vertices.end(), map_verts.cbegin(), map_verts.cend());
      indices.insert(indices.end(), map_inds.cbegin(), map_inds.cend());

      for(auto const& block : m_game.map().blocks()) {
        auto block_verts = get_gl_block_vertices(*block.get());
        u32 vertex_offset = vertices.size() / 6;
        vertices
          .insert(vertices.end(), block_verts.cbegin(), block_verts.cend());
        u32 block_inds[6] =
          {vertex_offset + 0,
           vertex_offset + 1,
           vertex_offset + 3,
           vertex_offset + 1,
           vertex_offset + 2,
           vertex_offset + 3};
        indices.insert(indices.end(), block_inds, block_inds + 6);
      }

      glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
      glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(f32),
        vertices.data(),
        GL_STATIC_DRAW
      );

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
      glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(u32),
        indices.data(),
        GL_STATIC_DRAW
      );

      glClearColor(.1f, 0.05f, 0.2f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      glUseProgram(m_shader_manager->program("simple_color").gl_program_id());
      glBindVertexArray(m_vao);
      glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
      glfwSwapBuffers(m_window);
      glBindVertexArray(0);
    }
  }

  auto Application::cleanup() -> void { glfwTerminate(); }

  auto Application::window() -> GLFWwindow* const { return m_window; }

  auto Application::get_gl_map_background_vertices() -> std::vector<f32>
  {
    utils::Color map_color {"#111111"};

    auto aspect_ratio = static_cast<f32>(m_window_width) / m_window_height;
    auto map_aspect_ratio = static_cast<f32>(m_game.map().width())
                          / m_game.map().height();
    f32 scale_x, scale_y;

    if(map_aspect_ratio <= aspect_ratio) {
      m_actual_map_height = m_window_height * 0.95f;
      auto block_width = m_actual_map_height / m_game.map().height();
      m_actual_map_width = block_width * m_game.map().width();

      scale_x = m_actual_map_width / m_window_width;
      scale_y = m_actual_map_height / m_window_height;
    }
    else {
      m_actual_map_width = m_window_width * 0.90f;
      auto block_height = m_actual_map_width / m_game.map().width();
      m_actual_map_height = block_height * m_game.map().height();

      scale_x = m_actual_map_width / m_window_width;
      scale_y = m_actual_map_height / m_window_height;
    }

    auto r = map_color.r() / 255.f;
    auto g = map_color.g() / 255.f;
    auto b = map_color.b() / 255.f;
    m_map_x = -scale_x;
    m_map_y = -scale_y;
    // clang-format off
    return {
      scale_x, scale_y, 0.0f, r, g, b,
      scale_x, -scale_y, 0.0f, r, g, b,
      -scale_x, -scale_y, 0.0f, r, g, b,
      -scale_x, scale_y, 0.0f, r, g, b
    };
    // clang-format on
  }

  auto Application::get_gl_block_vertices(bluks::game::Block const& block)
    -> std::vector<f32>
  {
    auto block_width_ndc = m_actual_map_width / m_window_width * 2.0f
                         / m_game.map().width();
    auto block_height_ndc = m_actual_map_height / m_window_height * 2.0f
                          / m_game.map().height();

    auto bl_x = m_map_x + block.position().x * block_width_ndc;
    auto bl_y = m_map_y + block.position().y * block_height_ndc;

    auto r = block.color().r() / 255.f;
    auto g = block.color().g() / 255.f;
    auto b = block.color().b() / 255.f;

    // clang-format off
return {
  bl_x, bl_y, 0.1f, r, g, b,                                       // bottom-left
  bl_x, bl_y + block_height_ndc, 0.1f, r, g, b,                    // top-left
  bl_x + block_width_ndc, bl_y + block_height_ndc, 0.1f, r, g, b,  // top-right
  bl_x + block_width_ndc, bl_y, 0.1f, r, g, b                      // bottom-right
};
  }
}  // namespace bluks::app
