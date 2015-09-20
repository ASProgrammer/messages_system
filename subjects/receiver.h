#ifndef RECEIVER_H
#define RECEIVER_H

#include "strucutures/queue.h"

namespace messaging {

class Sender;

class Receiver {
public:
    explicit operator Sender();

private:
    Queue m_queue;
};

}

#endif // RECEIVER_H
