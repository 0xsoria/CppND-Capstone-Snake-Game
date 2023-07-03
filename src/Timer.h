#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <thread>
#include <future>
#include <mutex>

class Timer {
private:
    int timer_duration;
    std::mutex _mutex;

public:
    Timer(int duration);
    ~Timer();
    int time_left;
    int TimerLeft();
    std::future<void> StartTimer();
    void ResetTimer();
    void RunTimer();
};

#endif