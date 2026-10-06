#pragma once

#include <source_location>

namespace ztd {

void log(
  const char *,
  const std::source_location loc = std::source_location::current()
);

[[noreturn]]
void log_n_abort(
  const char *,
  const std::source_location loc = std::source_location::current()
);

} /* namespace */
