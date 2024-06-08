#ifndef BALA_H
#define BALA_H

#include <cstdint>
#include <vector>

class bala {
public:
    virtual ~bala() = default;

    virtual std::vector<int32_t> get_pos() = 0;
    virtual void update() = 0;
    virtual void impactar() = 0;
};

#endif  // BALA_H
