#include <iostream>

#include <battery/embed.hpp>
#include <application/graphics/glad/glad.h>
#include <GLFW/glfw3.h>

#include <application/input/input_handler.h>
#include <application/application.h>

namespace bluks::app
{
  auto framebuffer_size_callback(GLFWwindow* window, int width, int height) -> void
  {
    glViewport(0, 0, width, height);
  }

  auto Application::get() -> Application*
  {
    static Application inst;
    return &inst;
  }

  Application::Application()
    : m_input_handler(nullptr)
    , m_game()
  {
    init_graphics();
    m_input_handler = input::InputHandler(m_window);
  }

  Application::~Application() { cleanup(); }

  auto Application::init_graphics() -> void
  {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(m_window_width, m_window_height, "Bluks", NULL, NULL);
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
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    u32 vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    char const* v_shader_src = b::embed<"src/shaders/default/default.vert.glsl">().data();
    char const* f_shader_src = b::embed<"src/shaders/default/default.frag.glsl">().data();

    glShaderSource(vertexShader, 1, &v_shader_src, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(not success) {
      glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      glfwTerminate();
    }

    u32 fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f_shader_src, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(not success) {
      glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
      glfwTerminate();
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(! success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
      glfwTerminate();
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
  }

  auto Application::run_graphics_loop() -> void
  {
    while(! glfwWindowShouldClose(m_window)) {
      m_input_handler.process_keys();

      float vertices[] = {
        0.5f,
        0.5f,
        0.0f,  // top right
        0.5f,
        -0.5f,
        0.0f,  // bottom right
        -0.5f,
        -0.5f,
        0.0f,  // bottom left
        -0.5f,
        0.5f,
        0.0f   // top left
      };
      unsigned int indices[] = {
        // note that we start from 0!
        0,
        1,
        3,  // first Triangle
        1,
        2,
        3   // second Triangle
      };
      u32 VBO, VAO, EBO;
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &EBO);
      glBindVertexArray(VAO);

      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);

      glBindBuffer(GL_ARRAY_BUFFER, 0);

      glBindVertexArray(0);

      glClearColor(.1f, 0.05f, 0.2f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      glfwSwapBuffers(m_window);
      glfwPollEvents();
    }
  }

  auto Application::cleanup() -> void { glfwTerminate(); }

  auto Application::window() -> GLFWwindow* const { return m_window; }

  auto Application::input_handler() -> input::InputHandler const& { return m_input_handler; }
}  // namespace bluks::app
