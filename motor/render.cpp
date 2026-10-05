#include <windows.h>
#include <stdlib.h>
#include <assert.h>
#include <new>

#include "render.hpp"
#include "log.hpp"

namespace ztd {

static HANDLE        hout   = INVALID_HANDLE_VALUE;
static RenderBuffer *buffer = nullptr;

RenderBuffer *render_init()
{
  if (buffer)
    return buffer;

  hout = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hout == INVALID_HANDLE_VALUE)
    log_and_abort("[ RENDER ] init: failed get console handle");

  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(hout, &csbi))
    log_and_abort("[ RENDER ] init: failed get console size");
  const u32 w = csbi.srWindow.Right  - csbi.srWindow.Left + 1;
  const u32 h = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1;

  buffer = new(std::nothrow) RenderBuffer();
  if (!buffer)
    log_and_abort("[ RENDER ] init: failed create screen buffer");
  if (!buffer->create(w, h))
    log_and_abort("[ RENDER ] init: failed create screen buffer");

  return buffer;
}

void render_deinit()
{
  assert(hout != INVALID_HANDLE_VALUE);
  assert(buffer);

  delete buffer;
  buffer = nullptr;
  hout   = INVALID_HANDLE_VALUE;
}

#pragma region Buffer

bool RenderBuffer::create(const u32 w, const u32 h)
{
  assert(!data_);
  assert(w && h);

  data_ = static_cast<char *>(malloc(w * h));
  if (!data_)
    return false;
  width_  = w;
  height_ = h;

  return true;
}

void RenderBuffer::destroy() {
  free(data_);
  data_ = nullptr;
}

void RenderBuffer::clear(const char c)
{
  assert(data_);
  for (u32 i = 0; i < width_ * height_; i++)
    data_[i] = c;
}

bool RenderBuffer::set(const u32 x, const u32 y, const char c)
{
  assert(data_);

  if (x >= width_ || y >= height_)
    return false;
  data_[y * width_ + x] = c;

  return true;
}

void RenderBuffer::show() const
{
  assert(hout != INVALID_HANDLE_VALUE);
  assert(data_);

  const char s[] = "\033[0;0H";

  WriteConsoleA(hout, s, sizeof(s), nullptr, nullptr);
  WriteConsoleA(hout, data_, width_ * height_, nullptr, nullptr);
}

#pragma endregion

} /* namespace */
