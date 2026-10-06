project('zalupa-tawer-defense', 'cpp',
  version : '1.0.0',
  default_options : [
    'warning_level=3',
    'cpp_std=c++11',
    'optimization=0',
    'cpp_eh=none'
  ]
)

src_motor = files(
  'motor/render.cpp',
  'motor/input.cpp',
  'motor/timer.cpp',
  'motor/log.cpp'
)

src_game = files(
  'game/main.cpp'
)

cppc = meson.get_compiler('cpp')
winmm_dll = cppc.find_library('winmm', required: true)

ztd_dll = shared_library(
  'ztd-motor',
  src_motor,
  dependencies: [winmm_dll]
)

executable(
  'ztd',
  src_game,
  link_with: ztd_dll
)
