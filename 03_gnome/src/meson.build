gnome_dice_sources = [
  'main.c',
  'gnome-dice-application.c',
  'gnome-dice-window.c',
]

gnome_dice_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
]

gnome_dice_sources += gnome.compile_resources('gnome-dice-resources',
  'gnome-dice.gresource.xml',
  c_name: 'gnome_dice'
)

executable('gnome-dice', gnome_dice_sources,
  dependencies: gnome_dice_deps,
       install: true,
)
