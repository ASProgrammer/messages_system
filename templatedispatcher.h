#ifndef TEMPLATEDISPATCHER_H
#define TEMPLATEDISPATCHER_H

#include <memory>

#include "messages/message.h"
#include "strucutures/queue.h"

namespace messaging {

template <typename PrevDisp, typename Msg, typename Func>
class TemplateDispatcher {
    template <typename Disp, typename OtherMsg, typename F>
    friend class TemplateDispatcher;
public:
    TemplateDispatcher(TemplateDispatcher&&);
    TemplateDispatcher(Queue*, PrevDisp*, Func&&);

    ~TemplateDispatcher() noexcept(false);

    TemplateDispatcher(const TemplateDispatcher&) = delete;
    TemplateDispatcher& operator = (const TemplateDispatcher&) = delete;

    template <typename OtherMsg, typename F>
    TemplateDispatcher<TemplateDispatcher, OtherMsg, F> handle(F&& f);

private:
    void wait_and_dispatch();
    bool dispatch(const std::shared_ptr<BaseMessage>& msg);

private:
    PrevDisp* m_prev_dispatcher;
    Func m_func;
    Queue* m_queue;
    bool m_chained;
};

}

namespace messaging {

template <typename PrevDisp, typename Msg, typename Func>
TemplateDispatcher<PrevDisp, Msg, Func>::TemplateDispatcher(TemplateDispatcher &&disp):
    m_queue { disp.m_queue }, m_chained { disp.m_chained },
    m_prev_dispatcher { disp.m_prev_dispatcher }, m_func { std::move(disp.m_func) }
{
    disp.m_chained = true;
}

template <typename PrevDisp, typename Msg, typename Func>
TemplateDispatcher<PrevDisp, Msg, Func>::TemplateDispatcher(Queue *q, PrevDisp *prev, Func &&f):
    m_queue { q }, m_prev_dispatcher { prev }, m_func { std::move(f) },
    m_chained { false }
{
    prev->m_chained = true;
}

template <typename PrevDisp, typename Msg, typename Func>
TemplateDispatcher<PrevDisp, Msg, Func>::~TemplateDispatcher() noexcept(false)
{
    if (!m_chained)
        wait_and_dispatch();
}

template <typename PrevDisp, typename Msg, typename Func>
bool TemplateDispatcher<PrevDisp, Msg, Func>::dispatch(const std::shared_ptr<BaseMessage>& msg)
{
    if (auto wrap = dynamic_cast<MessageWrapped<Msg>*>(msg.get())) {
        m_func(wrap->m_msg);
        return true;
    }

    return m_prev_dispatcher->dispatch(msg);
}

template <typename PrevDisp, typename Msg, typename Func>
void TemplateDispatcher<PrevDisp, Msg, Func>::wait_and_dispatch()
{
    while (true) {
        auto msg = m_queue->wait_and_pop();
        if (dispatch(msg))
            break;
    }
}

template <typename PrevDisp, typename Msg, typename Func>
template <typename OtherMsg, typename F>
TemplateDispatcher<TemplateDispatcher<PrevDisp, Msg, Func>, OtherMsg, F>
TemplateDispatcher<PrevDisp, Msg, Func>::handle(F&& f)
{
    return TemplateDispatcher<TemplateDispatcher, OtherMsg, F>(
        m_queue, this, std::forward<F>(f)
    );
}

}


#endif // TEMPLATEDISPATCHER_H
