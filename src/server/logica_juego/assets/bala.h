#ifndef BALA_H
#define BALA_H

#include <cstdint>
#include <vector>

class bala {
public:
    virtual ~bala() = default;

    [[nodiscard]] virtual std::vector<int32_t> get_pos() const = 0;
    virtual bool mover() = 0;
    virtual uint32_t impactar() = 0;
    [[nodiscard]] virtual int32_t get_id() const = 0;
    [[nodiscard]] virtual uint32_t disparar() = 0;
};

#endif  // BALA_H
