#include <iostream>
#include <graphics/app.h>

int main()
{
  auto app = bluks_gui::BluksApplication::application();

  try {
    app->run();
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
