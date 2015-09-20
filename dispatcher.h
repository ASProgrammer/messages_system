#ifndef DISPATCHER_H
#define DISPATCHER_H

namespace messaging {

class Queue;

struct CloseQueueMsg { };

class Dispatcher {
    template <typename Disp, typename Msg, typename Func>
    friend class TemplateDispatcher;

public:
    Dispatcher(Dispatcher&& disp);
    Dispatcher(Queue* queue);

    ~Dispatcher() noexcept(false);

    Dispatcher& operator = (const Dispatcher&) = delete;
    Dispatcher(const Dispatcher&) = delete;

    template <typename Message, typename Func>
    TemplateDispatcher<Dispatcher, Message, Func>
    handle(Func&& f);

private:
    void wait_and_dispatch();
    bool dispatch(const std::shared_ptr<BaseMessage>& msg);

private:
    Queue* m_queue;
    bool m_chained;
};

template <typename Message, typename Func>
TemplateDispatcher<Dispatcher, Message, Func>
Dispatcher::handle(Func&& f)
{
    return TemplateDispatcher<Dispatcher, Message, Func>(
        m_queue, this, std::forward<Func>(f)
    );
}

}

#endif // DISPATCHER_H
