#pragma once

#include "def.hpp"

namespace ztd {

class RenderBuffer
{
private:
  char *data_;
  u32   width_;
  u32   height_;

public:
   RenderBuffer() : data_(nullptr) {}
  ~RenderBuffer() { destroy(); }

  [[nodiscard]]
  bool create(const u32, const u32);
  void destroy();

  u32 width()  const { return width_; }
  u32 height() const { return height_; }

  void clear(const char);
  bool set(const u32, const u32, const char);
  void show() const;
};

RenderBuffer *render_init();
void          render_deinit();

} /* namespace */
