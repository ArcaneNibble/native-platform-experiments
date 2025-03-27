
#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define GNOME_DICE_TYPE_WINDOW (gnome_dice_window_get_type())

G_DECLARE_FINAL_TYPE (GnomeDiceWindow, gnome_dice_window, GNOME_DICE, WINDOW, AdwApplicationWindow)

G_END_DECLS

