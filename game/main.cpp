#include "../motor/ztd-motor.hpp"

int main()
{
  ztd::RenderBuffer *buf;
  ztd::InputEvent event;

  buf = ztd::render_init();
  ztd::input_init();
  ztd::timer_init();

  ztd::Map map(500, 300);
  map.clear(ztd::Block { '-', false });

  bool run = true;
  struct {
    i64 x, y;
  } cum = { 0, 0 };
  const i32 w = buf->width();
  const i32 h = buf->height();

  while (run) {
    if (event.wait()) {
      switch (event.code) {
      case 'Q': run = false; break;
      case 'A': cum.x--; break;
      case 'D': cum.x++; break;
      case 'W': cum.y--; break;
      case 'S': cum.y++; break;
      }
    }

    buf->clear(' ');

    i64 x  = cum.x - w / 2;
    i64 xb = 0;
    while (x <= cum.x + w / 2) {
      i64 y  = cum.y - h / 2;
      i64 yb = 0;
      while (y <= cum.y + h / 2) {
        ztd::Block b = map.get(x, y);
        if (b.ch == 0)
          buf->set(xb, yb, '#');
        else
          buf->set(xb, yb, b.ch);
        y++; yb++;
      }
      x++; xb++;
    }

    buf->show();
  }

  ztd::timer_deinit();
  ztd::render_deinit();
  return 0;
}
