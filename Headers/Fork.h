#ifndef FORK_H
#define FORK_H

#include <mutex>

class Fork {
public:
    std::mutex mutex;
};

#endif // FORK_H