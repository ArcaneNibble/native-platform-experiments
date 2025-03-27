gnome_dice_sources = [
  'main.c',
  'gnome-dice-application.c',
  'gnome-dice-window.c',
  'custom-dice-dialog.c',
]

gnome_dice_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
  dependency('gmodule-export-2.0'),
]

gnome_dice_sources += gnome.compile_resources('gnome-dice-resources',
  'gnome-dice.gresource.xml',
  c_name: 'gnome_dice'
)

executable('gnome-dice', gnome_dice_sources,
  dependencies: gnome_dice_deps,
       install: true,
)
