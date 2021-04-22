finance_incs += include_directories('editor')
finance_incs += include_directories('panel')
finance_incs += include_directories('views')

built_sources += gnome.compile_resources(
  'gui-resources',
  'gui.gresource.xml',
  c_name: 'gui',
)

sources += files(
  'finance-application.c',
  'finance-preferences-window.c',
  'finance-shortcuts-window.c',
  'finance-window.c',
)

subdir('editor')
subdir('panel')
subdir('views')
