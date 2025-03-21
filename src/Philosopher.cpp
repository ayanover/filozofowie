#include <iostream>
#include <chrono>
#include "../Headers/Philosopher.h"
#include "../Headers/ConstValues.h"

int Philosopher::current_id = 0;

Philosopher::Philosopher(
    Table& table,
    Fork& leftFork,
    Fork& rightFork):
    id(current_id++),
    table(table),
    left_fork(leftFork),
    right_fork(rightFork),
    life(&Philosopher::Dine, this),
    state(State::SLEEPING),
    meals_eaten(0) {}

Philosopher::~Philosopher() {
    if (life.joinable()) {
        life.join();
    }
}

State Philosopher::get_state() const {
    std::lock_guard<std::mutex> lock(mutex);
    return state;
}

int Philosopher::get_meals_eaten() const {
    std::lock_guard<std::mutex> lock(mutex);
    return meals_eaten;
}

void Philosopher::Eat() {
    if (&left_fork == &right_fork) {
        std::cerr << "Forks must be different!" << std::endl;
        return; // Exit the method if forks are the same
    }

    {
        std::lock_guard<std::mutex> lock(mutex);
        state = State::WAITING;
    }

    // Lock both forks atomically to prevent deadlock
    std::lock(left_fork.mutex, right_fork.mutex);

    std::lock_guard<std::mutex> left_lock(left_fork.mutex, std::adopt_lock);
    std::lock_guard<std::mutex> right_lock(right_fork.mutex, std::adopt_lock);

    {
        std::lock_guard<std::mutex> lock(mutex);
        state = State::EATING;
    }

    std::chrono::milliseconds eating_time(EAT_TIME);
    std::this_thread::sleep_for(eating_time);

    {
        std::lock_guard<std::mutex> lock(mutex);
        state = State::SLEEPING;
        meals_eaten++;
    }
}

void Philosopher::Think() {
    {
        std::lock_guard<std::mutex> lock(mutex);
        state = State::THINKING;
    }

    std::chrono::milliseconds thinking_time(THINK_TIME);
    std::this_thread::sleep_for(thinking_time);
}

void Philosopher::Dine() {
    table.wait_for_all();
    while (table.getPhilosophersNumber()) {
        Think();
        Eat();
    }
}