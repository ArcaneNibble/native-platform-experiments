
#include "config.h"

#include "gnome-dice-window.h"

struct _GnomeDiceWindow
{
	AdwApplicationWindow  parent_instance;

	/* Template widgets */
	AdwHeaderBar        *header_bar;
	GtkButton           *button;
};

static void roll_button(GAction         *_action,
                        GVariant        *_parameter,
                        GnomeDiceWindow *self) {
  int dice_roll = g_random_int_range (0, 20);
  char dice_roll_str[32];
  snprintf (dice_roll_str, sizeof(dice_roll_str), "%d", dice_roll + 1);

  gtk_button_set_label (self->button, dice_roll_str);
}

G_DEFINE_FINAL_TYPE (GnomeDiceWindow, gnome_dice_window, ADW_TYPE_APPLICATION_WINDOW)

static void
gnome_dice_window_class_init (GnomeDiceWindowClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/com/arcanenibble/Dice/gnome-dice-window.ui");
	gtk_widget_class_bind_template_child (widget_class, GnomeDiceWindow, header_bar);
	gtk_widget_class_bind_template_child (widget_class, GnomeDiceWindow, button);
}

static void
gnome_dice_window_init (GnomeDiceWindow *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));

  g_autoptr(GSimpleAction) roll_action = g_simple_action_new ("roll", 0);
  g_signal_connect (roll_action, "activate", G_CALLBACK (roll_button), self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION(roll_action));
}
