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

void draw_tps(ztd::RenderBuffer *buf, u8 n)
{
  for (i32 i = 2; i >= 0; i--) {
    buf->set(i, 0, n % 10 + '0');
    n /= 10;
  }
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

  i64 last_tick   = ztd::get_tick();
  u32 count_tps   = 0;
  u32 current_tps = 0;

  for (;;) {
    i64 start_tick = ztd::get_tick();

    if (start_tick - last_tick >= 10000000LL) {
      current_tps = count_tps;
      count_tps   = 0;
      last_tick  += 10000000LL;
    }

    count_tps++;

    if (event.get())
      if (event.ch == 'q')
        break;

    if (anime > 100.0)
      anime -= 100.0;
    x = buf->width()  / 2 + 20 * cos(anime);
    anime += 0.1;

    buf->clear(' ');
    draw_tps(buf, current_tps);
    draw_square(buf, x, y, 5);
    buf->show();

    ztd::sleep_tps(start_tick, 40);
  }

  ztd::timer_deinit();
  ztd::render_deinit();
  return 0;
}
