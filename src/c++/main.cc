#include <application/application.h>

int main()
{
  auto handler = bluks::app::Application {};
  handler.run_graphics_loop();
  return 0;
}
