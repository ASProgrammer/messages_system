#ifndef QUEUE_H
#define QUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>
#include <memory>

#include "messages/message.h"

namespace messaging {

class Queue {
public:
    template <typename Msg>
    void push(const Msg& msg);

    std::shared_ptr<BaseMessage> wait_and_pop();

private:
    std::queue<std::shared_ptr<BaseMessage>> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condition;
};

template <typename Msg>
void Queue::push(const Msg& msg)
{
    {
        std::lock_guard<std::mutex> locker { m_mutex };
        m_queue.push(std::make_shared<MessageWrapped<Msg>>(msg));
    }
    m_condition.notify_all();
}

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

#endif // QUEUE_H
