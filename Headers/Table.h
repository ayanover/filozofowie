//
// Created by rexiv on 16.01.2024.
//

#ifndef TABLE_H
#define TABLE_H


#include <vector>
#include <memory>
#include <condition_variable>
#include "Fork.h"


class Table {
    public:
        Table();
        ~Table();
        int getPhilosophersNumber() {
            return readyPhilosophersNumber;
        }
        void setPhilosophersNumber(int number) {
            readyPhilosophersNumber = number;
        }
        void wait_for_all();
        std::vector<std::unique_ptr<Fork> > forks;

    private:
        std::condition_variable cv;
        std::mutex cv_m;
        int readyPhilosophersNumber = 0;
};

#endif //TABLE_H