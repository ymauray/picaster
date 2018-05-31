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

#ifndef __JACK_MODULE_H_INCLUDED
#define __JACK_MODULE_H_INCLUDED

#include <jack/jack.h>

#include "JackClient.h"

class JackPorts;

class JackModule {

    private:
        const char* name;
        JackClient* client;
        bool        activated;

    public:
        [[deprecated]]
        JackPorts*  input_ports;
        [[deprecated]]
        JackPorts*  output_ports;

    public:
        JackModule(const char* name, JackClient* jack_client);
        void connectTo(JackModule* module);
        JackPorts* getInputPorts();
        JackPorts* getOutputPorts();
        jack_default_audio_sample_t** getInputPortsBuffers(jack_nframes_t nframes);
        jack_default_audio_sample_t** getOutputPortsBuffers(jack_nframes_t nframes);
        jack_client_t* getJackClient();
        void activate();

    public:
        virtual void process(jack_nframes_t nframes);

    /* Keep that */
    public:
        void connectTo(JackPorts* input_ports);

};

#endif