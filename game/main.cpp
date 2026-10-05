#include <math.h>

#include "../motor/render.hpp"
#include "../motor/input.hpp"
#include "../motor/timer.hpp"

void draw_square(ztd::RenderBuffer *buf, const i32 x, const i32 y, const i32 r)
{
  for (i32 i = x - r; i < x + r; i++)
    for (i32 j = y - r; j < y + r; j++)
      buf->set(i, j, '@');
}

int main()
{
  ztd::RenderBuffer *buf;
  ztd::InputEvent    event;

  buf = ztd::render_init();
  ztd::input_init();
  ztd::timer_init();

  double anime = 0.0;
  i32 x, y = buf->height() / 2;

  for (;;) {
    i64 start = ztd::get_tick();

    if (event.get())
      if (event.ch == 'q')
        break;

    if (anime > 100.0)
      anime -= 100.0;
    x = buf->width()  / 2 + 20 * cos(anime);
    anime += 0.1;

    buf->clear(' ');
    draw_square(buf, x, y, 5);
    buf->show();

    ztd::sleep_tps(start, 255);
  }

  ztd::timer_deinit();
  ztd::render_deinit();
  return 0;
}
