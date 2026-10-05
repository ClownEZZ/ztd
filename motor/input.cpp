#include <windows.h>
#include <assert.h>

#include "input.hpp"
#include "log.hpp"

namespace ztd {

static HANDLE hin = INVALID_HANDLE_VALUE;

void input_init()
{
  assert(hin == INVALID_HANDLE_VALUE);

  hin = GetStdHandle(STD_INPUT_HANDLE);
  if (hin == INVALID_HANDLE_VALUE)
    log_and_abort("[ INPUT ] init: failed get console handle");
}

bool InputEvent::get()
{
  assert(hin != INVALID_HANDLE_VALUE);
  DWORD n;
  GetNumberOfConsoleInputEvents(hin, &n);
  if (n > 0)
    return wait();
  return false;
}

bool InputEvent::wait()
{
  assert(hin != INVALID_HANDLE_VALUE);

  INPUT_RECORD ir;
  DWORD read;

  ReadConsoleInput(hin, &ir, 1, &read);
  if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown) {
    ch   = ir.Event.KeyEvent.uChar.AsciiChar;
    code = ir.Event.KeyEvent.wVirtualKeyCode;
  }
  else
    return false;

  return true;
}

} /* namespace */
