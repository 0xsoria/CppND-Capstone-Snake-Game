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
    int time_left;

public:
    Timer(int duration);
    ~Timer(); 
    Timer(const Timer &source);
    Timer &operator=(const Timer &source);
    Timer(Timer &&source);
    Timer &operator=(Timer &&source);

    bool paused = false;
    int TimerLeft();
    std::future<void> StartTimer();
    void ResetTimer();
    void RunTimer();
    void SetTimerTo(int value);
    void DecreaseTimer(int value);
    void PauseResume();
    bool IsPaused();
    void SetPaused(bool paused);
};

#endif