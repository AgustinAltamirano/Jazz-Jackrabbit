#include "socket_dummy.h"

SocketDummy::SocketDummy(): buffer_size(0), closed(false) {}

SocketDummy::~SocketDummy() {}

SocketAbstracto* SocketDummy::accept() { return new SocketDummy(); }
void SocketDummy::shutdown(int how) {}
int SocketDummy::close() { return 0; }
int SocketDummy::sendsome(const void* data, unsigned int sz, bool* was_closed) { return 0; }
int SocketDummy::recvsome(void* data, unsigned int sz, bool* was_closed) { return 0; }

int SocketDummy::sendall(const void* data, unsigned int sz, bool* was_closed) {
    std::vector<char> new_data(static_cast<const char*>(data), static_cast<const char*>(data) + sz);
    socket_buffer.insert(socket_buffer.end(), new_data.begin(), new_data.end());
    buffer_size += sz;
    *was_closed = closed;
    return sz;
}

int SocketDummy::recvall(void* data, unsigned int sz, bool* was_closed) {
    if (socket_buffer.empty()) {
        *was_closed = true;
        return 0;
    }
    int bytes_to_receive = std::min(static_cast<int>(sz), static_cast<int>(socket_buffer.size()));
    std::memcpy(static_cast<void*>(data), socket_buffer.data(), bytes_to_receive);
    socket_buffer.erase(socket_buffer.begin(), socket_buffer.begin() + bytes_to_receive);
    buffer_size -= bytes_to_receive;
    return bytes_to_receive;
}
