#ifndef MESSAGE_H
#define MESSAGE_H

namespace messaging {

struct BaseMessage {
    virtual ~BaseMessage();
};

template <typename Msg>
struct MessageWrapped : BaseMessage {
    Msg m_msg;

    explicit MessageWrapped(const Msg& msg):
        m_msg(msg)
    { }
};

}

#endif // MESSAGE_H
