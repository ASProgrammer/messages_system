#include "receiver.h"

#include "subjects/sender.h"
#include "dispatcher.h"

namespace messaging {

Receiver::operator Sender()
{
    return Sender { &m_queue };
}

Dispatcher Receiver::wait()
{
    return Dispatcher { &m_queue };
}

}
