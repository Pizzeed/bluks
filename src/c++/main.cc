#include <iostream>
#include <graphics/app.h>

int main()
{
  bluks_gui::BluksApplication app;

  try {
    app.run();
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
