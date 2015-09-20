#include <memory>

#include "dispatcher.h"
#include "strucutures/queue.h"
#include "messages/message.h"

namespace messaging {

Dispatcher::Dispatcher(Dispatcher &&disp):
    m_queue { disp.m_queue },
    m_chained { disp.m_chained }
{
    disp.m_chained = true;
}

Dispatcher::Dispatcher(Queue* queue):
    m_queue { queue }
{
    m_chained = false;
}

Dispatcher::~Dispatcher() noexcept(false)
{
    if (!m_chained)
        wait_and_dispatch();
}

bool Dispatcher::dispatch(const std::shared_ptr<BaseMessage> &msg)
{
    if (dynamic_cast<MessageWrapped<CloseQueueMsg>*>(msg.get()))
        throw CloseQueueMsg { };
    return false;
}

void Dispatcher::wait_and_dispatch()
{
    while (true) {
        auto msg = m_queue->wait_and_pop();
        dispatch(msg);
    }
}

}

