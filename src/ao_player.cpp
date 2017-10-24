#include <thread>
#include "ao_player.h"
#include <cstring>
#include <iostream>

AOPlayer::AOPlayer(Mixer& mixer)
    : mixer(mixer)
{

}

AOPlayer::~AOPlayer()
{
    ao_close(device);
    ao_shutdown();
}

void AOPlayer::init()
{
    ao_sample_format format;
    int default_driver;

    ao_initialize();
    default_driver = ao_default_driver_id();

    memset(&format, 0, sizeof(format));
    format.bits = 16;
    format.channels = 2;
    format.rate = mixer.SAMPLE_RATE;
    format.byte_format = AO_FMT_LITTLE;

    device = ao_open_live(default_driver, &format, NULL /* no options */);
    if (device == NULL) {
        throw std::runtime_error("aolib: error opening device");
    }
}

void AOPlayer::play()
{
    if (mixer.buffer_ready()) {
        buf = mixer.pop_buffer();
        std::thread([&]() {
            ao_play(device, reinterpret_cast<char*>(&buf[0]), buf.size()*sizeof(int16_t));
        }).detach();
    }
}
