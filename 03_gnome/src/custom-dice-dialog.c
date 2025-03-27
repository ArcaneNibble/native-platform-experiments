#include "config.h"

#include "custom-dice-dialog.h"

struct _CustomDiceDialog
{
	AdwDialog           parent_instance;

	/* Template widgets */
        GtkEntry            *entry;
};

G_DEFINE_FINAL_TYPE (CustomDiceDialog, custom_dice_dialog, ADW_TYPE_DIALOG)

G_MODULE_EXPORT void custom_dice_ok(GtkButton *button, gpointer _data) {
  CustomDiceDialog *self = CUSTOM_DICE_DIALOG (gtk_widget_get_ancestor (GTK_WIDGET(button), CUSTOM_DICE_TYPE_DIALOG));
  if (gtk_entry_get_text_length (self->entry)) {
    adw_dialog_close (ADW_DIALOG (self));
  }
}

int custom_dice_get_val(CustomDiceDialog *self) {
  GtkEntryBuffer *buffer = gtk_entry_get_buffer (self->entry);
  const char *text = gtk_entry_buffer_get_text (buffer);
  return strtol(text, 0, 10);
}

static void
custom_dice_dialog_class_init (CustomDiceDialogClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/com/arcanenibble/Dice/custom-dice-dialog.ui");
	gtk_widget_class_bind_template_child (widget_class, CustomDiceDialog, entry);
}

static void
custom_dice_dialog_init (CustomDiceDialog *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}

