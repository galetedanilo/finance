finance_incs += include_directories('entries')

built_sources += gnome.compile_resources(
  'transaction-resouces',
  'transaction.gresource.xml',
  c_name: 'transaction',
)

sources += files(
  'finance-transaction.c',
)

subdir('entries')
