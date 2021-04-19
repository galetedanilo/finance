finance_incs += include_directories('rows')

built_sources += gnome.compile_resources(
  'panel-resources',
  'panel.gresource.xml',
  c_name: 'panel',
)

sources += files(
  'finance-left-panel.c',
)

subdir('rows')
