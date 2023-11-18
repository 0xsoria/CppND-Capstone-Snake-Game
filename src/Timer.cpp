#include <iostream>
#include <thread>
#include <Timer.h>
#include <future>
#include <stdlib.h>

Timer::Timer(int duration) {
    timer_duration = duration;
    time_left = duration;
    std::cout << "Created "  << this << " an instance of Timer\n";
}

Timer:: ~Timer() {
    std::cout << "Finished " << timer_duration << " timer\n";
    std::cout << "Deallocated" << this << " instance of Timer\n";
}

//Copy Constructor
Timer::Timer(const Timer &source) {
    timer_duration = source.timer_duration;
    time_left = source.time_left;
}

//Copy assignment operator
Timer& Timer::operator=(const Timer &source) {
    std::cout << "Copy assignment called, source is: " << &source << " New is: " << this;
    if (this == &source) {
        return *this;
    }

    timer_duration = source.timer_duration;
    time_left = source.time_left;

    return *this;
}

//Move constructor
Timer::Timer(Timer &&source) {
    std::cout << "Move constructor called, source is: " << &source << " New is: " << this;
    timer_duration = source.timer_duration;
    time_left = source.time_left;
    source.SetTimerTo(0);
}

//Move assignment
Timer& Timer::operator=(Timer &&source) {
    std::cout << "Move assignment called, source is: " << &source << " New is: " << this;
    if (this == &source) {
        return *this;
    }

    timer_duration = source.timer_duration;
    time_left = source.time_left;
    source.SetTimerTo(0);

    return *this;
}

void Timer::SetTimerTo(int value) {
    std::lock_guard<std::mutex> lck(_mutex);
    timer_duration = value;
    time_left = value;
}

int Timer::TimerLeft() {
    return time_left;
}

void Timer::DecreaseTimer(int value) {
    std::lock_guard<std::mutex> lck(_mutex);
    time_left = value;
}

std::future<void> Timer::StartTimer() {
    std::cout << "Started " << timer_duration << " timer\n";
    std::future<void> asr = std::async(std::launch::async, [this]() {
        this->RunTimer();
    });

    return asr;
}

void Timer::RunTimer() {
    while (this->time_left <= this->timer_duration) {
        if (!this->paused) {
            if (time_left <= 0) {
                return;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::lock_guard<std::mutex> lck(_mutex);
            this->time_left -= 1;
        }
    }
}

void Timer::ResetTimer() {
    std::lock_guard<std::mutex> lck(_mutex);
    this->time_left = timer_duration + 1;
}

void Timer::PauseResume() {
    this->paused = this->paused ? false : true;
}

void Timer::SetPaused(bool paused) {
    this->paused = paused;
}

bool Timer::IsPaused() {
    return this->paused;
}