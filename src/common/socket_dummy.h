#ifndef SOCKET_DUMMY_H
#define SOCKET_DUMMY_H

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "constantes.h"
#include "socket.h"
#include "socket_abstracto.h"

class SocketDummy: public SocketAbstracto {
private:
    std::vector<char> socket_buffer;
    unsigned int buffer_size;
    bool closed;

public:
    SocketDummy();
    ~SocketDummy() override;

    int recvall(void* data, unsigned int sz, bool* was_closed) override;
    int sendall(const void* data, unsigned int sz, bool* was_closed) override;

    int sendsome(const void* data, unsigned int sz, bool* was_closed);
    int recvsome(void* data, unsigned int sz, bool* was_closed);

    SocketAbstracto* accept() override;
    void shutdown(int how) override;
    int close() override;
};
#endif
