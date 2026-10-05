#pragma once

#include "def.hpp"

namespace ztd {

void timer_init();
void timer_deinit();
i64  get_tick();
void sleep(const u64 time_ms);
void sleep_tps(const i64 start, const u8 tps);

} /* namespace */
