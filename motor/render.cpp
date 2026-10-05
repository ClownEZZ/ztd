#include <windows.h>
#include <stdlib.h>
#include <assert.h>

#include "render.hpp"
#include "log.hpp"
#include "def.hpp"

namespace ztd::render {

static HANDLE hout = INVALID_HANDLE_VALUE;
static struct {
  char *buf = nullptr;
  u32   width;
  u32   height;
} screen;

void init()
{
  assert(hout == INVALID_HANDLE_VALUE);
  assert(!screen.buf);

  hout = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hout == INVALID_HANDLE_VALUE)
    log_and_abort("[ RENDER ] init: failed get console handle");

  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(hout, &csbi))
    log_and_abort("[ RENDER ] init: failed get console size");
  screen.width  = csbi.srWindow.Right  - csbi.srWindow.Left + 1;
  screen.height = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1;

  screen.buf = static_cast<char *>(malloc(screen.width * screen.height));
  if (!screen.buf)
    log_and_abort("[ RENDER ] init: failed create screen buffer");
}

void deinit()
{
  assert(hout != INVALID_HANDLE_VALUE);
  assert(screen.buf);

  free(screen.buf);

  screen.buf = nullptr;
  hout       = INVALID_HANDLE_VALUE;
}

namespace buf {

void clear(const char c)
{
  assert(screen.buf);

  for (u32 i = 0; i < screen.width * screen.height; i++)
    screen.buf[i] = c;
}

void show()
{
  assert(hout != INVALID_HANDLE_VALUE);
  assert(screen.buf);

  const char s[] = "\033[0;0H";

  WriteConsoleA(hout, s, sizeof(s), nullptr, nullptr);
  WriteConsoleA(hout, screen.buf, screen.width * screen.height, nullptr, nullptr);
}

void set(const u32 x, const u32 y, const char c)
{
  assert(screen.buf);

  if (x >= screen.width || y >= screen.height)
    return;

  screen.buf[y * screen.width + x] = c;
}

} /* namespace buf */

} /* namespace */
