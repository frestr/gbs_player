#include "mixer.h"
#include <thread>
#include <iostream>
#include "util.h"
#include <cassert>

Mixer::Mixer()
    : buf_ready(false)
{
    timer.add_listener(this);
    timer.set_frequency(SAMPLING_RATE);
}

void Mixer::add_channel(Channel* channel)
{
    channels.push_back(channel);
}

bool Mixer::buffer_ready()
{
    return buf_ready;
}

Timer& Mixer::get_timer()
{
    return timer;
}

std::vector<int16_t> Mixer::pop_buffer()
{
    std::lock_guard<std::mutex> lock(buf_mutex);

    if (buffer.size() < buffer_threshold)
        return buffer;

    auto start = buffer.begin();
    auto end = start + buffer_threshold;
    std::vector<int16_t> vec(start, end);
    buffer.erase(start, end);

    return vec;
}

void Mixer::clock(Timer* timer)
{
    poll_channels();    
}

void Mixer::poll_channels()
{
    int16_t sample = 0;
    size_t channel_count = channels.size();
    for (auto& channel : channels) {
        uint8_t sample_raw = channel->get_sample();
        assert(sample_raw < 16);
        double volume = channel->get_true_volume();

        // 1. convert sample from range [0, 15] to [-32768, 32767],
        // 2. scale it (equally for all channels atm),
        // 3. adjust the volume and
        // 4. add the channel sample to the sample sum (mix)
        sample += (-32768 + 4369*sample_raw) * (1.0/channel_count) * volume;
    } 

    buf_mutex.lock();
    buffer.push_back(sample);

    if (buffer.size() >= 10*buffer_threshold) {
        // If the sysclock is perfectly synchronized to the sampling rate,
        // this shouldn't really happen. But as that is a bit hard to get
        // right, clear the buffer every now and then if it overfills
        // (this will result in some sound distortion/skipping, but it's not too
        // bad as long as it doesn't happen all the time). Fix later.
        buffer.clear();
        /* std::cout << "cleared buffer\n"; */
        /* buffer.erase(buffer.begin(), buffer.begin() + buffer_threshold); */
    }

    buf_ready = (buffer.size() >= buffer_threshold);
    buf_mutex.unlock();
}
