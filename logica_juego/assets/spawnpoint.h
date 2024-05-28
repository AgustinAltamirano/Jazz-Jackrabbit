#ifndef SPAWNPOINT_H
#define SPAWNPOINT_H

class spawnpoint {
public:
    int pos_x;
    int pos_y;
    spawnpoint(const int x, const int y) {
        pos_x = x;
        pos_y = y;
    }
};

#endif  // SPAWNPOINT_H
