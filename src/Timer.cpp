#include <iostream>
#include <thread>
#include <Timer.h>
#include <future>

Timer::Timer(int duration) {
    timer_duration = duration;
    time_left = duration;
}

Timer:: ~Timer() {
    std::cout << "Finished " << timer_duration << " timer\n";
}

int Timer::TimerLeft() {
    std::lock_guard<std::mutex> lck(_mutex);
    return time_left;
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
        if (time_left == 0) {
            return;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lck(_mutex);
        this->time_left -= 1;
        std::cout << "Time left " << time_left << "\n";
    }
}

void Timer::ResetTimer() {
    std::lock_guard<std::mutex> lck(_mutex);
    this->time_left = timer_duration + 1;
}