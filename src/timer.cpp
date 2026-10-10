#include <windows.h>
#include <assert.h>

#include "timer.hpp"
#include "log.hpp"

namespace ztd {

static HANDLE htimer = nullptr;

void timer_init() {
  assert(!htimer);
  timeBeginPeriod(1);
  htimer = CreateWaitableTimerW(nullptr, TRUE, nullptr);
  if (htimer == nullptr)
    log_n_abort("failed");
}

void timer_deinit() {
  timeEndPeriod(1);
  CloseHandle(htimer);
  htimer = nullptr;
}

i64 get_tick()
{
  LARGE_INTEGER tick;
  QueryPerformanceCounter(&tick);
  return tick.QuadPart;
}

void sleep(const u64 t) {
  LARGE_INTEGER sleep_tick;
  sleep_tick.QuadPart = -(t * 10000LL);
  if (!SetWaitableTimer(htimer, &sleep_tick, 0, nullptr, nullptr, 0))
    log_n_abort("failed set timer");
  WaitForSingleObject(htimer, INFINITE);
}

void sleep_tps(const i64 start, const u8 tps)
{
  LARGE_INTEGER sleep_tick;
  sleep_tick.QuadPart = -(10000000LL / tps) + (get_tick() - start);
  if (sleep_tick.QuadPart >= 0)
    return;
  if (!SetWaitableTimer(htimer, &sleep_tick, 0, nullptr, nullptr, 0))
    log_n_abort("failed set timer");
  WaitForSingleObject(htimer, INFINITE);
}

}
