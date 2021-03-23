enum_types = 'finance-enum-types'

built_sources = gnome.mkenums(
  enum_types,
     sources: enum_headers,
  c_template: enum_types + '.c.template',
  h_template: enum_types + '.h.template',
  install_header: true,
)

finance_incs = [
  include_directories('gui'),
  include_directories('theme'),
  include_directories('utils'),
]

sources = files()
subdir('gui')
subdir('theme')
subdir('utils')

finance_generated_sources_dep = declare_dependency(
  sources: built_sources,
)

finance_deps += finance_generated_sources_dep

libfinance = static_library(
    'finance-private',
              sources: sources,
  include_directories: finance_incs,
         dependencies: finance_deps,
              install: false,
)

libfinance_dep = declare_dependency(
            link_with: libfinance,
              sources: built_sources,
         dependencies: finance_deps,
  include_directories: finance_incs,
)


executable(
  meson.project_name(),
       files('main.c'),
          dependencies: libfinance_dep,
               install: true,
)
