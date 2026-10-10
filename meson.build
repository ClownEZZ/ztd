project('zalupa-tawer-defense-motor', 'cpp',
  version : '1.0.0',
  default_options : [
    'warning_level=3',
    'cpp_std=c++20',
    'cpp_eh=none'
  ]
)

src_motor = files(
  'src/render.cpp',
  'src/input.cpp',
  'src/timer.cpp',
  'src/log.cpp'
)

cppc = meson.get_compiler('cpp')
winmm_dll = cppc.find_library('winmm', required: true)

shared_library(
  'ztd',
  src_motor,
  dependencies: [winmm_dll]
)
