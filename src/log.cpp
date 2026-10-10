#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <source_location>

namespace ztd {

static void log_(const char *s, ...)
{
  FILE *f = fopen("ztd-log.txt", "a");
  if (!f)
    return;
  va_list ap;
  va_start(ap, s);

  vfprintf(f, s, ap);

  va_end(ap);
  fclose(f);
}

void log(
  const char *s,
  const std::source_location loc
) {
  const time_t fucking_date = time(nullptr);
  if (fucking_date == -1)
    log_("time: %s\n", strerror(errno));
  const struct tm *date = localtime(&fucking_date);
  if (!date)
    log_("localtime: %s\n", strerror(errno));

  if (date && fucking_date != -1) {
    log_(
      "%d-%02d-%02d %02d:%02d:%02d  %s  %s: %s\n",
      date->tm_year + 1900,
      date->tm_mon  + 1,
      date->tm_mday,
      date->tm_hour,
      date->tm_min,
      date->tm_sec,
      loc.file_name(),
      loc.function_name(),
      s
    );
  }
  else
    log_("%s  %s: %s\n", loc.file_name(), loc.function_name(), s);
}

void log_n_abort(
  const char *s,
  const std::source_location loc
) {
  log(s, loc);
  abort();
}

} /* namespace */
