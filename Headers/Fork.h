//
// Created by rexiv on 16.01.2024.
//

#ifndef FORK_H
#define FORK_H

#include <mutex>

class Fork {
    public:
        std::mutex mutex;
};

#endif //FORK_H
