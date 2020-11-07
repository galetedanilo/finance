inc_dirs = [
  include_directories('gui'),
]

finance_sources = [
  'main.c',
  'gui/finance-application.c',
  'gui/finance-preferences-window.c',
  'gui/finance-shortcuts-window.c',
  'gui/finance-window.c',
]

finance_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
]

gnome = import('gnome')

finance_sources += gnome.compile_resources('finance-resources',
  'finance.gresource.xml',
  c_name: 'finance'
)

executable('finance', finance_sources,
  dependencies: finance_deps,
  include_directories: inc_dirs,
  install: true,
)
