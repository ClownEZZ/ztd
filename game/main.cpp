#include "../motor/render.hpp"

int main()
{
  ztd::render::init();

  ztd::render::buf::clear('-');
  ztd::render::buf::set(10, 10, '@');
  ztd::render::buf::show();

  ztd::render::deinit();
  return 0;
}
