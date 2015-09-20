#ifndef RECEIVER_H
#define RECEIVER_H

#include "strucutures/queue.h"

namespace messaging {

class Sender;
class Dispatcher;

class Receiver {
public:
    operator Sender();
    Dispatcher wait();

private:
    Queue m_queue;
};

}

#endif // RECEIVER_H
