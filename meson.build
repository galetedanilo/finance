project(
  'gnome-finance',
	      'c',
          version: '0.1.0',
          license: 'GPL3+',
    meson_version: '>= 0.50.0',
  default_options: [ 'warning_level=2',
                     'c_std=gnu11',
                   ],
)

src_dir = join_paths(meson.source_root(), 'src')

config_h = configuration_data()
config_h.set_quoted('PACKAGE_VERSION', meson.project_version())
config_h.set_quoted('GETTEXT_PACKAGE', meson.project_name())
config_h.set_quoted('LOCALEDIR', join_paths(get_option('prefix'), get_option('localedir')))
config_h.set_quoted('APPLICATION_ID', 'org.gnome.Finance')

configure_file(
  output: 'finance-config.h',
  configuration: config_h,
)
add_project_arguments([
  '-I' + meson.build_root(),
], language: 'c')

#################################################
#		DEPENDENCIES			#
#################################################
finance_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
]

i18n = import('i18n')
gnome = import('gnome')

#################################################
#		   SUBDIRS			#
#################################################
subdir('data')
subdir('src')
subdir('po')

meson.add_install_script('build-aux/meson/postinstall.py')
