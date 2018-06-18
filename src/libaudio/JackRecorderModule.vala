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

namespace LibAudio
{ 
    public class JackRecorderModule : JackModule
    {
        private bool recording;
        private Jack.Ringbuffer rb;

        private size_t sample_size = sizeof(Jack.DefaultAudioSample);

        public JackRecorderModule(string name, JackClient jack_client)
        {
            base(name, jack_client);
            input_ports = jack_client.create_input_ports(name);
            recording = false;
            rb = Jack.Ringbuffer.create(2 * sample_size * 8192);
            jack_client.register_module(this);
        }

        public override void process(Jack.NFrames nframes)
        {
            
        }
    }
}