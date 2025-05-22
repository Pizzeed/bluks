#include <graphics/graphics_handler.h>

int main()
{
  auto handler = bluks::graphics::GraphicsHandler {};
  handler.run_graphics_loop();
  return 0;
}
