#pragma once

#include <assert.h>

#include "def.hpp"
#include "log.hpp"

namespace ztd {

struct Block
{
  char ch;
  bool is_solid;

  ZTD_INLINE Block() :
    ch(0), is_solid(false)
  {}
  ZTD_INLINE Block(const char c, const bool is) :
    ch(c), is_solid(is)
  {}
};

class Map
{
private:
  Block *data_;
  u32    width_;
  u32    height_;

public:
  Map(const u32, const u32);

  ZTD_INLINE ~Map() {
    free(data_);
    data_ = nullptr;
  }

  ZTD_INLINE u32 width()  const { return width_; }
  ZTD_INLINE u32 height() const { return height_; }

  void  set(const u32, const u32, const Block);
  Block get(const u32, const u32);

  ZTD_INLINE void clear(const Block b) {
    for (u32 i = 0; i < width_ * height_; i++)
      data_[i] = b;
  }
};

ZTD_INLINE Map::Map(const u32 w, const u32 h)
{
  assert(w && h);

  data_ = static_cast<Block *>(malloc(sizeof(Block) * w * h));
  if (!data_)
    log_n_abort("no mem");
  width_  = w;
  height_ = h;
}

ZTD_INLINE void Map::set(const u32 x, const u32 y, const Block b)
{
  assert(x < width_);
  assert(y < height_);
  data_[y * width_ + x] = b;
}

ZTD_INLINE Block Map::get(const u32 x, const u32 y)
{
  if (x < width_ && y < height_)
    return data_[y * width_ + x];
  return {};
}

}
