#include <iostream>
#include "../motor/render.hpp"

int main()
{
  auto buf = ztd::render_init();

  buf->clear('-');
  buf->set(10, 10, '@');
  buf->show();

  ztd::render_deinit();
  return 0;
}
