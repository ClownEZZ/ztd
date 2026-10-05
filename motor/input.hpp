#pragma once

#include "def.hpp"

namespace ztd::input {

struct Event {
  char ch   = 0;
  u16  code = 0;
};

void  init();
Event get_event();
Event get_event_hook();

} /* namespace */
