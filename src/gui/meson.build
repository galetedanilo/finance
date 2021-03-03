finance_incs += include_directories('transaction')
finance_incs += include_directories('pane')

built_sources += gnome.compile_resources(
  'gui-resources',
  'gui.gresource.xml',
  c_name: 'gui',
)

sources += files(
  'finance-application.c',
  'finance-shortcuts-window.c',
  'finance-window.c',
)

subdir('pane')
subdir('transaction')
