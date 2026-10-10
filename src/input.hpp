#pragma once

#include "def.hpp"

namespace ztd {

struct InputEvent
{
  char ch;
  u16  code;

  /**
   * Проверяет есть ли событие.
   * Если есть, возвращает его.
   */
  bool get();

  /**
   * Пока в очереди нету события
   * программа остановится на этой функции
   */
  bool wait();
};

/**
 * В случае "неудачи" инициализации вызовет abort)
 */
void input_init();

} /* namespace */
