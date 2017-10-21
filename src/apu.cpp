#include "apu.h"

APU::APU(SystemClock& clock)
    : frame_sequencer(256)
{
    // Prob. not what the APU sets these values to by default, but keep
    // them like this for the moment
    square1.set_volume(0);
    square2.set_volume(0);
    wave.enable_sound(false);
    wave.set_volume(0);
    noise.set_parameters(6, 1, 0);
    noise.set_volume(3);

    // Make the system clock clock the frame sequencer & all channels
    clock.add_timer(&frame_sequencer);
    clock.add_timer(&square1.get_timer());
    clock.add_timer(&square2.get_timer());
    clock.add_timer(&wave.get_timer());
    clock.add_timer(&noise.get_timer());
    clock.add_timer(&mixer.get_timer());

    // Make the frame sequencer clock all channels
    frame_sequencer.add_listener(&square1);
    frame_sequencer.add_listener(&square2);
    frame_sequencer.add_listener(&wave);
    frame_sequencer.add_listener(&noise);

    // Add all channels to the mixer
    mixer.add_channel(&square1);
    mixer.add_channel(&square2);
    mixer.add_channel(&wave);
    mixer.add_channel(&noise);
}

Mixer& APU::get_mixer()
{
    return mixer;
}
