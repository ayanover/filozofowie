#include "../Headers/Table.h"

Table::Table() : philosophers_number(0) {
    for (int i = 0; i < PHILOSOPHERS_NUMBER; i++) {
        forks.push_back(std::make_shared<Fork>());
    }
}

Table::~Table() {
    forks.clear();
}

int Table::getPhilosophersNumber() {
    std::lock_guard<std::mutex> lock(mutex);
    return philosophers_number;
}

void Table::setPhilosophersNumber(int number) {
    std::lock_guard<std::mutex> lock(mutex);
    philosophers_number = number;
    cv.notify_all();
}

void Table::wait_for_all() {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this]() { return philosophers_number == PHILOSOPHERS_NUMBER; });
}