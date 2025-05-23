#include <application/application.h>

int main()
{
  auto app = bluks::app::Application::get();
  app->run_graphics_loop();
  return 0;
}
