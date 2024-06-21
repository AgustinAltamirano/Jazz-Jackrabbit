#ifndef SOCKET_ABSTRACTO_H
#define SOCKET_ABSTRACTO_H

class SocketAbstracto
{
public:
    virtual int sendsome(const void *data, unsigned int sz, bool *was_closed) = 0;
    virtual int recvsome(void *data, unsigned int sz, bool *was_closed) = 0;

    virtual int sendall(const void *data, unsigned int sz, bool *was_closed) = 0;
    virtual int recvall(void *data, unsigned int sz, bool *was_closed) = 0;

    virtual SocketAbstracto *accept() = 0;

    virtual void shutdown(int how) = 0;

    virtual int close() = 0;

    virtual ~SocketAbstracto() {}
};
#endif
