#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "Fork.h"

class Table {
private:
    int philosophers_number;
    std::mutex mutex;
    std::condition_variable cv;

public:
    std::vector<std::shared_ptr<Fork>> forks;

    Table();
    ~Table();

    int getPhilosophersNumber();
    void setPhilosophersNumber(int number);
    void wait_for_all();
};

#endif // TABLE_H