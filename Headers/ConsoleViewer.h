#ifndef CONSOLE_VIEWER_H
#define CONSOLE_VIEWER_H

#include <vector>
#include <memory>
#include <thread>
#include "Philosopher.h"
#include "Table.h"

class ConsoleViewer {
private:
    std::vector<std::shared_ptr<Philosopher>>& philosophers;
    Table& table;
    std::thread thread;

    void update();
    void display_state();

public:
    ConsoleViewer(std::vector<std::shared_ptr<Philosopher>>& philosophers, Table& table);
    ~ConsoleViewer();
};

#endif // CONSOLE_VIEWER_H