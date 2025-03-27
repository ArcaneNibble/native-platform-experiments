
#include "config.h"

#include "gnome-dice-window.h"
#include "custom-dice-dialog.h"

struct _GnomeDiceWindow
{
	AdwApplicationWindow  parent_instance;

        GSettings *settings;

	/* Template widgets */
	AdwHeaderBar        *header_bar;
	GtkButton           *button;
        GtkMenuButton       *menu_button;

        int dice_max_roll;
};

static void roll_button(GAction         *_action,
                        GVariant        *_parameter,
                        GnomeDiceWindow *self) {
  int dice_roll = g_random_int_range (0, self->dice_max_roll);
  char dice_roll_str[32];
  snprintf (dice_roll_str, sizeof(dice_roll_str), "%d", dice_roll + 1);

  gtk_button_set_label (self->button, dice_roll_str);
}

static void update_dice_type(GnomeDiceWindow *self) {
  g_settings_set_int (self->settings, "dice-type", self->dice_max_roll);

  char dice_max_str[32];
  snprintf (dice_max_str, sizeof(dice_max_str), "D%d", self->dice_max_roll);
  gtk_menu_button_set_label (self->menu_button, dice_max_str);
}

static void fixed_dice(GAction         *_action,
                       GVariant        *parameter,
                       GnomeDiceWindow *self) {
  const char *dice_max_str = g_variant_get_string (parameter, 0);
  self->dice_max_roll = strtol(dice_max_str, 0, 10);
  update_dice_type (self);
}

static void custom_dice_done(CustomDiceDialog *dice_dialog,
                             GnomeDiceWindow  *dice_window) {
  int maybe_new_roll = custom_dice_get_val (dice_dialog);
  if (maybe_new_roll) {
    dice_window->dice_max_roll = maybe_new_roll;
    update_dice_type (dice_window);
  }
}

static void custom_dice(GAction         *_action,
                        GVariant        *_parameter,
                        GnomeDiceWindow *self) {
  CustomDiceDialog *dice_dialog = g_object_new (CUSTOM_DICE_TYPE_DIALOG, 0);
  g_signal_connect_object (dice_dialog, "closed", G_CALLBACK(custom_dice_done), self, 0);
  adw_dialog_present (ADW_DIALOG (dice_dialog), GTK_WIDGET(self));
}

G_DEFINE_FINAL_TYPE (GnomeDiceWindow, gnome_dice_window, ADW_TYPE_APPLICATION_WINDOW)

static void gnome_dice_window_finalize(GObject *gobject) {
  GnomeDiceWindow *self = GNOME_DICE_WINDOW (gobject);

  g_clear_object (&self->settings);

  G_OBJECT_CLASS (gnome_dice_window_parent_class)->finalize (gobject);
}

static void
gnome_dice_window_class_init (GnomeDiceWindowClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
        GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

        gobject_class->finalize = gnome_dice_window_finalize;

	gtk_widget_class_set_template_from_resource (widget_class, "/com/arcanenibble/Dice/gnome-dice-window.ui");
	gtk_widget_class_bind_template_child (widget_class, GnomeDiceWindow, header_bar);
	gtk_widget_class_bind_template_child (widget_class, GnomeDiceWindow, button);
	gtk_widget_class_bind_template_child (widget_class, GnomeDiceWindow, menu_button);
}

static void
gnome_dice_window_init (GnomeDiceWindow *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));

  self->settings = g_settings_new ("com.arcanenibble.Dice");

  self->dice_max_roll = g_settings_get_int (self->settings, "dice-type");
  update_dice_type (self);

  g_autoptr(GSimpleAction) roll_action = g_simple_action_new ("roll", 0);
  g_signal_connect (roll_action, "activate", G_CALLBACK (roll_button), self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION(roll_action));

  g_autoptr(GSimpleAction) fixed_dice_action = g_simple_action_new ("fixed_dice", G_VARIANT_TYPE_STRING);
  g_signal_connect (fixed_dice_action, "activate", G_CALLBACK (fixed_dice), self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION(fixed_dice_action));

  g_autoptr(GSimpleAction) custom_dice_action = g_simple_action_new ("custom_dice", 0);
  g_signal_connect (custom_dice_action, "activate", G_CALLBACK (custom_dice), self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION(custom_dice_action));
}

