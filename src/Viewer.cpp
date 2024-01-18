//
// Created by rexiv on 18.01.2024.
//

#include <unistd.h>
#include "../Headers/Viewer.h"
#include "../Headers/ConstValues.h"

void Viewer::init() {
    initscr();
    noecho(); // no user input is being shown on the screen
    box(stdscr, 0, 0);

    getmaxyx(stdscr, params.y_max, params.x_max);
    params.x_margin = params.x_max / 10;
    params.y_margin = params.y_max / 10;
    params.separator = params.x_max / 1;

    int column_width = (params.separator - params.x_margin) / 2;

    mvwprintw(stdscr, params.y_margin / 2, params.x_max / 2 - 11, "");
    mvwprintw(stdscr, params.y_max - params.y_margin / 2, params.x_max / 2 - 11, "Jakub Grych");

    refresh();

    window = derwin(stdscr, params.y_max - 2 * params.y_margin,
                    params.separator - params.x_margin, params.y_margin, params.x_margin);
    box(window, 0, 0);

    wprintw(window, "Philosophers");

    mvwprintw(window, 2, 2, "Id");
    mvwprintw(window, 2, column_width, "State");

    mvwhline(window, 4, 1, ACS_HLINE, params.separator - params.x_margin - 2);
    mvwvline(window, 1, column_width - 2, ACS_VLINE, params.y_max - 2 * params.y_margin - 2);

    for (int i = 0; i < PHILOSOPHERS_NUMBER; i++) {
        mvwprintw(window, 2 * i + 5, 3, "%d", philosophers[i]->get_id());
    }

    touchwin(window);
    wrefresh(window);
}


void Viewer::update_screen() {
    int column_width = (params.separator - params.x_margin) / 2;

    for (int i = 0; i < PHILOSOPHERS_NUMBER; i++) {
        switch (philosophers[i]->get_state()) {
            case State::EATING:
                mvwprintw(window, 2 * i + 5, column_width + 1, "EATING  ");
            break;

            case State::THINKING:
                mvwprintw(window, 2 * i + 5, column_width + 1, "THINKING");
            break;

            case State::WAITING:
                mvwprintw(window, 2 * i + 5, column_width + 1, "WAITING ");
            break;

            default:
                mvwprintw(window, 2 * i + 5, column_width + 1, "SLEEPING");
            break;
        }
    }
    touchwin(window);
    wrefresh(window);
}


void Viewer::update() {
    while (table.getPhilosophersNumber()) {
        update_screen();
    }
}

Viewer::~Viewer() {
    delwin(window);
    endwin();

    philosophers.clear();
    thread.join();
}

Viewer::Viewer(std::vector<std::shared_ptr<Philosopher> > &philosophers, Table &table) : philosophers(
        philosophers), table(table) {
    init();
    while (!table.getPhilosophersNumber());
    thread = std::thread(&Viewer::update, this);
}


