
#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define GNOME_DICE_TYPE_APPLICATION (gnome_dice_application_get_type())

G_DECLARE_FINAL_TYPE (GnomeDiceApplication, gnome_dice_application, GNOME_DICE, APPLICATION, AdwApplication)

GnomeDiceApplication *gnome_dice_application_new (const char        *application_id,
                                                  GApplicationFlags  flags);

G_END_DECLS
