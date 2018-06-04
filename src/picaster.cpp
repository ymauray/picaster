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

#include <unistd.h>
#include <iostream>
#include <assert.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "JackClient.h"
#include "JackRecorderModule.h"
#include "JackFaderModule.h"
#include "JackFilePlayerModule.h"

/*
int
main(int argc, char** argv)
{
    const int RB_SIZE = 14;
    Float32RingBuffer* ringbuf = new Float32RingBuffer(RB_SIZE);
    assert(ringbuf->r_buf_avail() == 0);
    assert(ringbuf->w_buf_avail() == RB_SIZE);

    float* w_testbuf = new float[12] { 0.0, 0.0, 0.1, 0.2, 0.2, 0.4, 0.3, 0.6, 0.4, 0.8, 0.5, 1.0 };
    float* r_testbuf = new float[6];

    ringbuf->write(w_testbuf, 12);
    assert(ringbuf->r_buf_avail() == 12);
    assert(ringbuf->w_buf_avail() == (RB_SIZE - 12));

    memset(r_testbuf, 0, 6 * sizeof(float));
    ringbuf->read(r_testbuf, 4);
    assert(ringbuf->r_buf_avail() == 8);
    assert(ringbuf->w_buf_avail() == (RB_SIZE - 8));
    assert(r_testbuf[0] == 0.0f);
    assert(r_testbuf[1] == 0.0f);
    assert(r_testbuf[2] == 0.1f);
    assert(r_testbuf[3] == 0.2f);

    memset(r_testbuf, 0, 6 * sizeof(float));
    ringbuf->read(r_testbuf, 6);
    assert(ringbuf->r_buf_avail() == 2);
    assert(ringbuf->w_buf_avail() == (RB_SIZE - 2));
    assert(r_testbuf[0] == 0.2f);
    assert(r_testbuf[1] == 0.4f);
    assert(r_testbuf[2] == 0.3f);
    assert(r_testbuf[3] == 0.6f);

    ringbuf->write(w_testbuf, 12);
    assert(ringbuf->r_buf_avail() == 14);
    assert(ringbuf->w_buf_avail() == (RB_SIZE - 14));
}
*/

int
main(int argc, char** argv)
{
    JackClient* jack_client = JackClient::getInstance("PiCaster");

    jack_client->setJackdPath("/usr/bin/jackd");
#ifdef USE_DUMMY_DRIVER
    jack_client->setDriver("dummy");
#else
    jack_client->setDriver("alsa");
#endif
    jack_client->setSampleRate("48000");
    jack_client->setFramesPerPeriod("512");
    jack_client->setPeriodsPerBuffer("3");
    jack_client->setInputDevice("CODEC");
    jack_client->setOutputDevice("CODEC");
    jack_client->startJack();

    JackRecorderModule* recorder = new JackRecorderModule("recorder", jack_client);
    JackFaderModule* master_fader = new JackFaderModule("master_fader", jack_client);
    JackModule* dj_fader = new JackFaderModule("dj_fader", jack_client);
    //JackPorts* deck_a = jack_client->createOutputPorts("deck_a");
    JackFilePlayerModule* deck_a = new JackFilePlayerModule("deck_a", jack_client);
    JackPorts* deck_b = jack_client->createOutputPorts("deck_b");
    JackModule* decks_fader = new JackFaderModule("decks_fader", jack_client);
    JackPorts* fx = jack_client->createOutputPorts("fx");
    JackModule* fx_fader = new JackFaderModule("fx_fader", jack_client);

    JackPorts* playback_ports = jack_client->getPlaybackPorts();
    JackPorts* capture_ports = jack_client->getCapturePorts();

    master_fader->setSliderValue(1.0); /* 0 dBFS */
    master_fader->connectTo(playback_ports);
    master_fader->connectTo(recorder);

    capture_ports->connectTo(dj_fader);
    dj_fader->connectTo(master_fader);

    deck_a->connectTo(decks_fader);
    deck_b->connectTo(decks_fader);
    decks_fader->connectTo(master_fader);

    fx->connectTo(fx_fader);
    fx_fader->connectTo(master_fader);

    recorder->startRecording("/tmp/picaster.flac");
    //deck_a->playFile("/home/yannick/Téléchargements/Kwizat_Haterach_-_Le_bon_moment.flac");
    //deck_a->playFile("/data/Musique/picaster/stereo_square_4hz_0.8.flac");
    //deck_a->playFile("/home/yannick/Musique/demo.flac");
    deck_a->playFile("/home/yannick/Musique/JekK_-_Strong.mp3");

    int bloc = 500;
    while (--bloc > 0)
    {
        usleep(50000);
    }

    recorder->stopRecording();
    
    jack_client->stopJack();

    return 0;
}