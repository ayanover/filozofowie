#include <iostream>
#include <thread>
#include "../headers/Table.h"
#include "../headers/Philosopher.h"
#include "../headers/ConstValues.h"
#include "../headers/Viewer.h"

using namespace std;

void Run() {
    Table table;
    vector<shared_ptr<Philosopher> > philosophers;

    for (int i = 0; i < PHILOSOPHERS_NUMBER; i++) {
        if (i != PHILOSOPHERS_NUMBER - 1) {
            philosophers.emplace_back(new Philosopher(table, *table.forks[i], *table.forks[i + 1]));
        } else {
            philosophers.emplace_back(new Philosopher(table, *table.forks[i], *table.forks[0]));
        }
    }

    Viewer *viewer = new Viewer(philosophers, table);

    this_thread::sleep_for(chrono::seconds(FEAST_TIME));
    table.setPhilosophersNumber(0);

    delete viewer;
    philosophers.clear();
}

int main() {
    Run();
    return 0;
}
