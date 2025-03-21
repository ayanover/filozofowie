#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <thread>
#include <mutex>
#include "Table.h"
#include "Fork.h"
#include "Enums.h"

class Philosopher {
private:
    static int current_id;
    
    int id;
    Table& table;
    Fork& left_fork;
    Fork& right_fork;
    std::thread life;
    State state;
    int meals_eaten;
    mutable std::mutex mutex;

    void Eat();
    void Think();
    void Dine();

public:
    Philosopher(Table& table, Fork& leftFork, Fork& rightFork);
    ~Philosopher();

    int get_id() const { return id; }
    State get_state() const;
    int get_meals_eaten() const;
};

#endif // PHILOSOPHER_H