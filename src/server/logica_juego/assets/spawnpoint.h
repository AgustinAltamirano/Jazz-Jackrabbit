#ifndef SPAWNPOINT_H
#define SPAWNPOINT_H

#include <cstdint>

class spawnpoint {
public:
    int32_t pos_x;
    int32_t pos_y;
    spawnpoint(const int32_t x, const int32_t y) {
        pos_x = x;
        pos_y = y;
    }
};

#endif  // SPAWNPOINT_H
