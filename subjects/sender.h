#ifndef SENDER_H
#define SENDER_H

#include "strucutures/queue.h"

namespace messaging {

class Sender {
public:
    explicit Sender(Queue* queue = nullptr);

    template <typename Msg>
    void send(const Msg& msg);

private:
    Queue* m_queue;
};

template <typename Msg>
void Sender::send(const Msg& msg)
{
    if (m_queue)
        m_queue->push(msg);
}

}

#endif // SENDER_H
