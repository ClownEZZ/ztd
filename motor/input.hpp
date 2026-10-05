#pragma once

#include "def.hpp"

namespace ztd {

struct InputEvent
{
  char ch;
  u16  code;

  bool get();
  bool wait();
};

void input_init();

} /* namespace */
