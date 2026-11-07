#include "Tropicamel.h"

#include <chrono>
#include <thread>
#include <cstdio>

Tropicamel::Tropicamel() = default;

void Tropicamel::setSim(bool enabled) {
    mSimulation = enabled;
}

void Tropicamel::start() {
    mTimestampFromStart = 0;
    mTick = 0;

    std::printf("Tropicamel");
    std::printf(mSimulation == true ? " (running simulation)\n" : "\n");
}

void Tropicamel::tick() {
    ++mTick;
    ++mTimestampFromStart;
}

void Tropicamel::update() {
    // Hardware and input processing will go here.
}

void Tropicamel::loop() {
    using namespace std::chrono_literals;

    auto nextTick = std::chrono::steady_clock::now() + 1s;
    while (true) {
        update();

        auto now = std::chrono::steady_clock::now();
        while (now >= nextTick) {
            tick();
            nextTick += 1s;
        }

        std::this_thread::sleep_for(10ms);
    }
}
