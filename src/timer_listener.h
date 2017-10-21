#pragma once

class Timer;

class TimerListener
{
public:
    virtual void clock(Timer* timer) = 0;
};
