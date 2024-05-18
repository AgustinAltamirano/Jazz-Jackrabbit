#ifndef SERVIDOR_H_
#define SERVIDOR_H_


#include <string>

class Servidor {
private:
    std::string &servname;
public:
    explicit Servidor(std::string &servname);

    void run();

    Servidor(const Servidor &) = delete;

    Servidor &operator=(const Servidor &) = delete;
};

#endif  // SERVIDOR_H_
