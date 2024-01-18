//
// Created by rexiv on 18.01.2024.
//

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <string>
#include <thread>
#include "Fork.h"
#include "Table.h"
#include "Enums.h"

static int current_id = 0;

class Philosopher {
    public:

        Philosopher(Table &table, Fork &rightFork, Fork &leftFork);
        ~Philosopher();

        void Dine();
        void Think();
        void Eat();
        int get_id() {
            return id;
        }

        State get_state() { return state; }
        std::mutex mutex;
        std::condition_variable cv;

    private:
        int id;
        volatile State state;
        Table &table;
        Fork &left_fork;
        Fork &right_fork;
        std::thread life;
};

#endif //PHILOSOPHER_H
