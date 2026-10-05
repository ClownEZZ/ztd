#include "../motor/render.hpp"
#include "../motor/input.hpp"

int main()
{
  ztd::RenderBuffer *buf;
  ztd::InputEvent    event;

  struct {
    i32 x = 0;
    i32 y = 0;
  } obj;

  buf = ztd::render_init();
  ztd::input_init();

  for (;;) {
    if (event.wait()) {
      if (event.ch == 'q')
        break;
      if (event.code == 65) obj.x--; /* a */
      if (event.code == 68) obj.x++; /* d */
      if (event.code == 87) obj.y--; /* w */
      if (event.code == 83) obj.y++; /* s */
    }

    buf->clear(' ');
    buf->set(obj.x, obj.y, '@');
    buf->show();
  }

  ztd::render_deinit();
  return 0;
}
