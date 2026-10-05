#include <windows.h>
#include <assert.h>

#include "input.hpp"
#include "log.hpp"

namespace ztd::input {

static HANDLE hin = INVALID_HANDLE_VALUE;

void init()
{
  assert(hin == INVALID_HANDLE_VALUE);

  hin = GetStdHandle(STD_INPUT_HANDLE);
  if (hin == INVALID_HANDLE_VALUE)
    log_and_abort("[ INPUT ] init: failed get console handle");
}

Event get_event()
{
  DWORD n;
  GetNumberOfConsoleInputEvents(hin, &n);
  if (n > 0)
    return get_event_hook();
  return {};
}

Event get_event_hook()
{
  assert(hin != INVALID_HANDLE_VALUE);

  INPUT_RECORD ir;
  DWORD read;
  Event res;

  ReadConsoleInput(hin, &ir, 1, &read);
  if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown) {
    res.ch   = ir.Event.KeyEvent.uChar.AsciiChar;
    res.code = ir.Event.KeyEvent.wVirtualKeyCode;
  }

  return res;
}

} /* namespace */
