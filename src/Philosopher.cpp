#include <iostream>
#include "../Headers/Philosopher.h"
#include "../Headers/ConstValues.h"
#include "../Headers/Enums.h"

using namespace std;

Philosopher::Philosopher(
    Table &table,
    Fork &rightFork,
    Fork &leftFork):
    id(current_id++),
    table(table),
    right_fork(rightFork),
    left_fork(leftFork),
    life(&Philosopher::Dine, this),
    state(State::SLEEPING) {}

Philosopher::~Philosopher() {
    life.join();
}

void Philosopher::Eat() {
    if (&left_fork == &right_fork)
        cerr << "Forks must be the same!";

    state = State::WAITING;

    lock(left_fork.mutex, right_fork.mutex);

    lock_guard<mutex> left_lock(left_fork.mutex, adopt_lock);
    lock_guard<mutex> right_lock(right_fork.mutex, adopt_lock);

    state = State::EATING;

    chrono::milliseconds eating_time(EAT_TIME);
    this_thread::sleep_for(eating_time);
    
    cv.notify_all();
}

void Philosopher::Think() {
    state = State::THINKING;

    chrono::milliseconds thinking_time(THINK_TIME);
    this_thread::sleep_for(thinking_time);
}

void Philosopher::Dine() {
    table.wait_for_all();
    while (table.getPhilosophersNumber()) {
        Think();
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this]() { return state == State::WAITING; });
        Eat();
    }
}
