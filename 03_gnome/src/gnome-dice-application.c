
#include "config.h"

#include "gnome-dice-application.h"
#include "gnome-dice-window.h"

struct _GnomeDiceApplication
{
	AdwApplication parent_instance;
};

G_DEFINE_FINAL_TYPE (GnomeDiceApplication, gnome_dice_application, ADW_TYPE_APPLICATION)

GnomeDiceApplication *
gnome_dice_application_new (const char        *application_id,
                            GApplicationFlags  flags)
{
	g_return_val_if_fail (application_id != NULL, NULL);

	return g_object_new (GNOME_DICE_TYPE_APPLICATION,
	                     "application-id", application_id,
	                     "flags", flags,
	                     NULL);
}

static void
gnome_dice_application_activate (GApplication *app)
{
	GtkWindow *window;

	g_assert (GNOME_DICE_IS_APPLICATION (app));

	window = gtk_application_get_active_window (GTK_APPLICATION (app));

	if (window == NULL)
		window = g_object_new (GNOME_DICE_TYPE_WINDOW,
		                       "application", app,
		                       NULL);

	gtk_window_present (window);
}

static void
gnome_dice_application_class_init (GnomeDiceApplicationClass *klass)
{
	GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

	app_class->activate = gnome_dice_application_activate;
}

static void
gnome_dice_application_about_action (GSimpleAction *action,
                                     GVariant      *parameter,
                                     gpointer       user_data)
{
	static const char *developers[] = {"ArcaneNibble", NULL};
	GnomeDiceApplication *self = user_data;
	GtkWindow *window = NULL;

	g_assert (GNOME_DICE_IS_APPLICATION (self));

	window = gtk_application_get_active_window (GTK_APPLICATION (self));

	adw_show_about_dialog (GTK_WIDGET (window),
	                       "application-name", "Demo Dice",
	                       "application-icon", "com.arcanenibble.Dice",
	                       "developer-name", "ArcaneNibble",
	                       "version", "0.1.0",
	                       "developers", developers,
	                       "copyright", "© 2025 ArcaneNibble",
	                       NULL);
}

static void
gnome_dice_application_quit_action (GSimpleAction *action,
                                    GVariant      *parameter,
                                    gpointer       user_data)
{
	GnomeDiceApplication *self = user_data;

	g_assert (GNOME_DICE_IS_APPLICATION (self));

	g_application_quit (G_APPLICATION (self));
}

static const GActionEntry app_actions[] = {
	{ "quit", gnome_dice_application_quit_action },
	{ "about", gnome_dice_application_about_action },
};

static void
gnome_dice_application_init (GnomeDiceApplication *self)
{
	g_action_map_add_action_entries (G_ACTION_MAP (self),
	                                 app_actions,
	                                 G_N_ELEMENTS (app_actions),
	                                 self);
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "app.quit",
	                                       (const char *[]) { "<primary>q", NULL });

	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "win.fixed_dice::4",
	                                       (const char *[]) { "<primary>1", NULL });
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "win.fixed_dice::6",
	                                       (const char *[]) { "<primary>2", NULL });
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "win.fixed_dice::8",
	                                       (const char *[]) { "<primary>3", NULL });
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "win.fixed_dice::10",
	                                       (const char *[]) { "<primary>4", NULL });
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "win.fixed_dice::12",
	                                       (const char *[]) { "<primary>5", NULL });
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "win.fixed_dice::20",
	                                       (const char *[]) { "<primary>6", NULL });
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "win.custom_dice",
	                                       (const char *[]) { "<primary>7", NULL });
}
