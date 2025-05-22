#include <application/application.h>

int main()
{
  auto handler = bluks::graphics::Application {};
  handler.run_graphics_loop();
  return 0;
}
