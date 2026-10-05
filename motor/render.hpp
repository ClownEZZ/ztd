#pragma once

#include "def.hpp"

namespace ztd::render {

void init();
void deinit();

namespace buf {

void clear(const char);
void show();
void set(const u32, const u32, const char);

} /* namespace buf */

} /* namespace */
