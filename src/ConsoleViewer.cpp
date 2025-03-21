#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "../Headers/ConsoleViewer.h"
#include "../Headers/ConstValues.h"

void ConsoleViewer::display_state() {
    std::console.clear();

    std::cout << "Dining Philosophers Simulation" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << std::endl;

    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(10) << "STATE"
              << std::setw(10) << "MEALS EATEN" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    for (const auto& philosopher : philosophers) {
        std::cout << std::left << std::setw(5) << philosopher->get_id();

        switch (philosopher->get_state()) {
            case State::EATING:
                std::cout << std::setw(10) << "EATING";
                break;
            case State::THINKING:
                std::cout << std::setw(10) << "THINKING";
                break;
            case State::WAITING:
                std::cout << std::setw(10) << "WAITING";
                break;
            default:
                std::cout << std::setw(10) << "SLEEPING";
                break;
        }

        std::cout << std::setw(10) << philosopher->get_meals_eaten() << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Press Ctrl+C to exit" << std::endl;
}

void ConsoleViewer::update() {
    while (table.getPhilosophersNumber()) {
        display_state();
        std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_INTERVAL));
    }
}

ConsoleViewer::ConsoleViewer(std::vector<std::shared_ptr<Philosopher>>& philosophers, Table& table)
    : philosophers(philosophers), table(table) {
    thread = std::thread(&ConsoleViewer::update, this);
}

ConsoleViewer::~ConsoleViewer() {
    if (thread.joinable()) {
        thread.join();
    }
}