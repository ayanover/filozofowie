#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>
#include "../Headers/Table.h"
#include "../Headers/Philosopher.h"
#include "../Headers/ConsoleViewer.h"
#include "../Headers/ConstValues.h"

void Run() {
    Table table;
    std::vector<std::shared_ptr<Philosopher>> philosophers;

    for (int i = 0; i < PHILOSOPHERS_NUMBER; i++) {
        if (i != PHILOSOPHERS_NUMBER - 1) {
            philosophers.emplace_back(new Philosopher(table, *table.forks[i], *table.forks[i + 1]));
        } else {
            philosophers.emplace_back(new Philosopher(table, *table.forks[0], *table.forks[i]));
        }
    }

    auto viewer = std::make_unique<ConsoleViewer>(philosophers, table);

    table.setPhilosophersNumber(PHILOSOPHERS_NUMBER);

    std::cout << "\nRunning simulation for " << FEAST_TIME << " seconds...\n" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(FEAST_TIME));

    table.setPhilosophersNumber(0);

    std::cout << "\033[2J\033[1;1H";

    std::cout << "\n╔═════════════════════════════════════╗" << std::endl;
    std::cout << "║      Simulation Results Summary      ║" << std::endl;
    std::cout << "╚═════════════════════════════════════╝" << std::endl;

    std::cout << "\n╔═══════════════╦═══════════════╗" << std::endl;
    std::cout << "║ Philosopher ID ║   Meals Eaten  ║" << std::endl;
    std::cout << "╠═══════════════╬═══════════════╣" << std::endl;

    for (const auto& philosopher : philosophers) {
        std::cout << "║ " << std::setw(13) << philosopher->get_id()
                  << " ║ " << std::setw(13) << philosopher->get_meals_eaten() << " ║" << std::endl;
    }

    std::cout << "╚═══════════════╩═══════════════╝" << std::endl;

    int total_meals = 0;
    for (const auto& philosopher : philosophers) {
        total_meals += philosopher->get_meals_eaten();
    }

    std::cout << "\n╔═════════════════════════════════════════════╗" << std::endl;
    std::cout << "║ Total meals eaten: " << std::setw(23) << total_meals << " ║" << std::endl;
    std::cout << "║ Average meals per philosopher: " << std::setw(12)
              << std::fixed << std::setprecision(2)
              << static_cast<float>(total_meals) / PHILOSOPHERS_NUMBER << " ║" << std::endl;
    std::cout << "╚═════════════════════════════════════════════╝" << std::endl;

    philosophers.clear();
}

int main() {
    try {
        Run();
        std::cout << "Dining philosophers simulation completed." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}