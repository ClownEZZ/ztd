#include <windows.h>
#include <new>

#include "render.hpp"

namespace ztd {

static HANDLE        hout   = INVALID_HANDLE_VALUE;
static RenderBuffer *buffer = nullptr;

RenderBuffer *render_init()
{
  if (buffer)
    return buffer;

  hout = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hout == INVALID_HANDLE_VALUE)
    log_n_abort("failed get console handle");

  CONSOLE_CURSOR_INFO ci;
  if (GetConsoleCursorInfo(hout, &ci)) {
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(hout, &ci);
  }

  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(hout, &csbi))
    log_n_abort("failed get console size");
  const u32 w = csbi.srWindow.Right  - csbi.srWindow.Left + 1;
  const u32 h = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1;

  buffer = new(std::nothrow) RenderBuffer(w, h);
  if (!buffer)
    log_n_abort("failed create screen buffer");

  return buffer;
}

void render_deinit()
{
  assert(hout != INVALID_HANDLE_VALUE);
  assert(buffer);

  CONSOLE_CURSOR_INFO ci;
  if (GetConsoleCursorInfo(hout, &ci)) {
    ci.bVisible = TRUE;
    SetConsoleCursorInfo(hout, &ci);
  }

  delete buffer;
  buffer = nullptr;
  hout   = INVALID_HANDLE_VALUE;
}

void RenderBuffer::show() const
{
  assert(hout != INVALID_HANDLE_VALUE);

  const char s[] = "\033[0;0H";

  WriteConsoleA(hout, s, sizeof(s), nullptr, nullptr);
  WriteConsoleA(hout, data_, width_ * height_, nullptr, nullptr);
}

} /* namespace */
