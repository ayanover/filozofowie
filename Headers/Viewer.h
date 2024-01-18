//
// Created by rexiv on 18.01.2024.
//

#ifndef VIEWER_H
#define VIEWER_H

#include <thread>
#include <ncurses.h>
#include "Philosopher.h"


class Viewer {
public:
    Viewer(std::vector<std::shared_ptr<Philosopher> > &philosophers, Table &table);

    ~Viewer();

private:
    void init();
    void update_screen();
    void update();
    std::thread thread;
    WINDOW *window;
    std::vector<std::shared_ptr<Philosopher>> &philosophers;
    Table &table;

    struct Window_params {
        int x_max;
        int y_max;
        int x_margin;
        int y_margin;
        int separator;
    } params;
};

#endif //VIEWER_H
