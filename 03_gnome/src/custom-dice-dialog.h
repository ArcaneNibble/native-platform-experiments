#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define CUSTOM_DICE_TYPE_DIALOG (custom_dice_dialog_get_type())

G_DECLARE_FINAL_TYPE (CustomDiceDialog, custom_dice_dialog, CUSTOM_DICE, DIALOG, AdwDialog)

int custom_dice_get_val(CustomDiceDialog *self);

G_END_DECLS
