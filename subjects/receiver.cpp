#include "receiver.h"

#include "subjects/sender.h"

namespace messaging {

Receiver::operator Sender()
{
    return Sender { &m_queue };
}

}
