#include "queue.h"

namespace messaging {

std::shared_ptr<BaseMessage> Queue::wait_and_pop()
{
    std::unique_lock<std::mutex> locker { m_mutex };
    m_condition.wait(locker, [&]() -> bool {
        return !m_queue.empty();
    });

    auto result = m_queue.front();
    m_queue.pop();

    return result;
}

}

