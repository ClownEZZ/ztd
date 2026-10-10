#pragma once

#include <string.h>
#include <assert.h>

#include "def.hpp"
#include "log.hpp"

namespace ztd {

class RenderBuffer
{
private:
  char *data_;
  u32   width_;
  u32   height_;

public:
  RenderBuffer(const u32, const u32);

  ZTD_INLINE ~RenderBuffer() {
    free(data_);
    data_ = nullptr;
  }

  ZTD_INLINE u32 width()  const { return width_; }
  ZTD_INLINE u32 height() const { return height_; }

  ZTD_INLINE void clear(const char c) {
    memset(data_, c, width_ * height_);
  }

  void set(const u32, const u32, const char);
  void show() const;
};

ZTD_INLINE RenderBuffer::RenderBuffer(const u32 w, const u32 h)
{
  assert(w && h);

  data_ = static_cast<char *>(malloc(w * h));
  if (!data_)
    log_n_abort("no mem");
  width_  = w;
  height_ = h;
}

ZTD_INLINE void RenderBuffer::set(const u32 x, const u32 y, const char c)
{
  assert(x < width_);
  assert(y < height_);
  data_[y * width_ + x] = c;
}

/**
 * В случае неудачи вызывает abort
 */
RenderBuffer *render_init();

void render_deinit();

} /* namespace */
