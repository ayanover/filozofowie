//
// Created by rexiv on 18.01.2024.
//

#include "../Headers/Table.h"
#include "../Headers/ConstValues.h"
#include "../Headers/Philosopher.h"

Table::Table() {
    readyPhilosophersNumber = 0;
    for (int i = 0; i < PHILOSOPHERS_NUMBER; i++) {
        forks.emplace_back(new Fork());
    }
}

Table::~Table() {
    forks.clear();
}

void Table::wait_for_all() {
    std::unique_lock<std::mutex> lk(cv_m);
    setPhilosophersNumber(getPhilosophersNumber()+1);
    cv.wait(lk, [&] { return getPhilosophersNumber() >= PHILOSOPHERS_NUMBER; });
    cv.notify_all();
}


