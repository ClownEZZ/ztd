#include <iostream>
#include "../motor/input.hpp"

int main()
{
  ztd::input::init();

  ztd::input::Event event;
  std::cout << "press 'q' to exit";
  for (;;) {
    //event = ztd::input::get_event();
    event = ztd::input::get_event_hook();
    std::cout << event.code << '\t';
    if (event.ch >= ' ')
      std::cout << '\'' << event.ch << '\'';
    std::cout << '\n';
    if (event.ch == 'q')
      break;
  }

  return 0;
}
