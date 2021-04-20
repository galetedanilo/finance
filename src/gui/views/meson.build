finance_incs += include_directories('children')

built_sources += gnome.compile_resources(
  'views-resources',
  'views.gresource.xml',
  c_name: 'views',
)

sources += files(
  'finance-view.c',
  'finance-transaction-view.c',
)

subdir('children')
