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

class StartStreamerButton : Gtk.ToggleButton
{
    public StartStreamerButton()
    {
        Object(
            label: "Stream"
        );

        this.add_accelerator("clicked", PiCaster.App.accel_group, Gdk.Key.s, 0, Gtk.AccelFlags.VISIBLE);

        set_sensitive(false);
        PiCaster.App.bus.jack_started.connect(jack_started);
        PiCaster.App.bus.jack_stopped.connect(jack_stopped);

        toggled.connect(() => {
            if (get_active()) PiCaster.App.bus.lock_jack();
            else PiCaster.App.bus.unlock_jack();
        });
    }

    public void jack_started()
    {
        set_sensitive(true);
    }

    public void jack_stopped()
    {
        set_sensitive(false);
    }
}