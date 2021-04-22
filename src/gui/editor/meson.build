finance_incs += include_directories('entries')

built_sources += gnome.compile_resources(
  'editor-resouces',
  'editor.gresource.xml',
  c_name: 'editor',
)

sources += files(
  'finance-transaction-editor.c',
)

subdir('entries')
