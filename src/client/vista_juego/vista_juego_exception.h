#ifndef VISTA_JUEGO_EXCEPTION_H
#define VISTA_JUEGO_EXCEPTION_H

#include <exception>
#include <string>
#include <utility>

class VistaJuegoException final: public std::exception {
private:
    std::string message;

public:
    explicit VistaJuegoException(const char* message): message(message) {}

    explicit VistaJuegoException(std::string message): message(std::move(message)) {}

    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

#endif  // VISTA_JUEGO_EXCEPTION_H
