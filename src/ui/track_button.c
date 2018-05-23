/**
    PiCaster is a podcast recording and streaming application,
    easy to use for beginners, but with enough functionality
    to suit the needs of intermediate or experienced podcasters.

    Copyright (C) 2018  Yannick Mauray

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "track_button.h"

#include <stdlib.h>
#include <string.h>
#include <taglib/tag_c.h>

#include "../audio/gstreamer.h"
#include "../context.h"

void
on_trk_button_clicked(GtkButton* button, gpointer user_data)
{
    g_print("on_trk_button_clicked\n");
    TrackButtonData* track_button_data = (TrackButtonData*)g_object_get_data(G_OBJECT(button), "button_data");
    if (track_button_data->file_path == NULL)
    {
        g_print("nothing to play\n");
    }
    else
    {
        if (track_button_data->audio_context == NULL)
        {
            g_print("->p_gstreamer_play_track\n");
            track_button_data->audio_context = p_gstreamer_play_track(track_button_data->file_path);
        }
        else
        {
            g_print("->p_gstreamer_stop_track\n");
            p_gstreamer_stop_track(track_button_data->audio_context);
            track_button_data->audio_context = NULL;
        }
    }
}

void
p_gtk_init_track_buttons()
{
    for (int i = 1; i <= 8; i++)
    {
        gchar* button_name = g_strdup_printf("trk%d_button", i);
        GtkButton* button = GTK_BUTTON(gtk_builder_get_object(context.builder, button_name));
        TrackButtonData* track_button_data = (TrackButtonData*)calloc(1, sizeof(TrackButtonData));
        track_button_data->button_name = g_strdup_printf("TRK%d", i);
        g_object_set_data(G_OBJECT(button), "button_data", track_button_data);
        GtkLabel* label = GTK_LABEL(gtk_bin_get_child(GTK_BIN(button)));
        g_print("%s\n", gtk_label_get_text(label));
        gtk_label_set_ellipsize(label, PANGO_ELLIPSIZE_END);
        gtk_label_set_max_width_chars(label, 24);
    }

    for (int i = 1; i <= 6; i++)
    {
        TrackButtonData* track_button_data = (TrackButtonData*)calloc(1, sizeof(TrackButtonData));
        gchar* button_name = g_strdup_printf("fx%d_button", i);
        GtkButton* button = GTK_BUTTON(gtk_builder_get_object(context.builder, button_name));
        g_object_set_data(G_OBJECT(button), "button_data", track_button_data);
    }
}

static gchar*
ellipsize(const gchar* source)
{
    if (strlen(source) <= 24)
    {
        return g_strdup(source);
    }
    else
    {
        gchar* target = (gchar*)calloc(28, sizeof(gchar));
        memcpy(target, source, 24 * sizeof(gchar));
        memcpy(target + 24, "...", 3);
        return target;
    }
}

gboolean
on_trk_button_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    GdkEventButton* event_button = (GdkEventButton*)event;
    if (event_button->button == 3)
    {
        TrackButtonData* track_button_data = (TrackButtonData*)g_object_get_data(G_OBJECT(widget), "button_data");
        if (track_button_data->file_path == NULL)
        {
            g_print("Loading file\n");
            GtkWidget* file_chooser_dialog = gtk_file_chooser_dialog_new("Open file", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
            gint res = gtk_dialog_run(GTK_DIALOG(file_chooser_dialog));
            if (res == GTK_RESPONSE_ACCEPT)
            {
                GtkFileChooser* chooser = GTK_FILE_CHOOSER(file_chooser_dialog);
                track_button_data->file_path = gtk_file_chooser_get_filename(chooser);
                TagLib_File* taglib_file = taglib_file_new(track_button_data->file_path);
                if (taglib_file == NULL)
                {
                    g_printerr("Error : %s could not be opened\n", track_button_data->file_path);
                }
                else
                {
                    if (!taglib_file_is_valid(taglib_file))
                    {
                        g_printerr("Error : %s is invalid or has no information\n", track_button_data->file_path);
                    }
                    else
                    {
                        const TagLib_AudioProperties* audioproperties = taglib_file_audioproperties(taglib_file);
                        int length = taglib_audioproperties_length(audioproperties);
                        int seconds = length % 60;
                        int minutes = (length - seconds) / 60;
                        gchar* duration = g_strdup_printf("%02d:%02d", minutes, seconds);

                        TagLib_Tag* tag = taglib_file_tag(taglib_file);
                        char* title = taglib_tag_title(tag);
                        char* artist = taglib_tag_artist(tag);
                        gchar* track_info = g_strdup_printf("%s - %s", artist, title);

                        gchar* short_label = ellipsize(title);
                        gtk_button_set_label(GTK_BUTTON(widget), short_label);
                        g_free(short_label);

                        g_free(duration);
                        g_free(track_info);
                    }
                    taglib_tag_free_strings();
                    taglib_file_free(taglib_file);
                }
                /*
                gchar* short_label = ellipsize(track_button_data->file_path);
                gtk_button_set_label(GTK_BUTTON(widget), short_label);
                g_free(short_label);
                */
            }
            gtk_widget_destroy(file_chooser_dialog);
        }
        else
        {
            g_free(track_button_data->file_path);
            track_button_data->file_path = NULL;
            gtk_button_set_label(GTK_BUTTON(widget), track_button_data->button_name);
        }
    }
    return FALSE;
}
