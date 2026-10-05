project('zalupa-tawer-defense', 'cpp',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++11',
    'optimization=0',
    'cpp_eh=none'
  ]
)

source = files(
  'game/main.cpp',
  'motor/render.cpp',
  'motor/input.cpp',
  'motor/timer.cpp',
  'motor/log.cpp'
)

executable('ztd', source,
  link_args: ['-lwinmm']
)
