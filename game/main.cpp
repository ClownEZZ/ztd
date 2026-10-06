#include "../motor/ztd-motor.hpp"

struct Obj {
  i64 x, y;
};

int main()
{
  ztd::RenderBuffer *buf;
  ztd::InputEvent event;

  buf = ztd::render_init();
  ztd::input_init();
  ztd::timer_init();

  ztd::Map map(120, 40);

{ /* это заразно?? */
  map.clear(ztd::Block { '#', true });
  srand(ztd::get_tick());
  u32 empty_block = 0;
  Obj all_chache = { rand() % map.width(), rand() % map.height() };
  while (empty_block < map.width() * map.height() / 100 * 30) {
    ztd::Block tmp = map.get(all_chache.x, all_chache.y);
    if (tmp.is_solid) {
      map.set(all_chache.x, all_chache.y, ztd::Block { '.', false });
      empty_block++;
    }
    switch (rand() % 4) {
    case 0:
      if (all_chache.x - 1 >= 0)
        all_chache.x--;
      break;
    case 1:
      if (all_chache.x + 1 < map.width())
        all_chache.x++;
      break;
    case 2:
      if (all_chache.y - 1 >= 0)
        all_chache.y--;
      break;
    case 3:
      if (all_chache.y + 1 < map.height())
        all_chache.y++;
      break;
    }
  }
} /* это пиздец... */

  bool run = true;
  Obj  cum = { map.width() / 2, map.height() / 2 };
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

    i64 x  = cum.x - w / 2;
    i64 xb = 0;
    while (x <= cum.x + w / 2) {
      i64 y  = cum.y - h / 2;
      i64 yb = 0;
      while (y <= cum.y + h / 2) {
        ztd::Block b = map.get(x, y);
        if (b.ch == 0)
          buf->set(xb, yb, ' ');
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
