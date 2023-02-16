#include "Metronome.h"
#include "Utilities.h"
#include <boost/bind.hpp>
#include <iostream>

Metronome::Metronome(boost::asio::io_context& io_context) {
    subsystem = HOUSEKEEPING;
    state = CMD_SEND;

    tick_period_seconds = boost::asio::chrono::seconds(1);
    timer = new boost::asio::steady_timer(io_context, tick_period_seconds);
    timer->async_wait(boost::bind(&Metronome::tick, this));
}

Metronome::~Metronome() {}

void Metronome::run() {
    timer->async_wait(boost::bind(&Metronome::tick, this));
    // io_context.run();
}

void Metronome::tick() {

    std::cout << "tick\n";
    std::cout << "\tsubsystem: " << std::to_string(subsystem);
    std::cout << "\tstate: " << std::to_string(state) << "\n";

    Metronome::update();

    // update timer
    timer->expires_at(timer->expires_at() + tick_period_seconds);
    timer->async_wait(boost::bind(&Metronome::tick, this));
}

void Metronome::update() {
    if(state == DATA_STORE) {
        ++subsystem;
    }
    ++state;
    // modify tick_period if necessary
}
