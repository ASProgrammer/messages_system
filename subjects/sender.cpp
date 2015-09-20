#include "sender.h"

namespace messaging {

Sender::Sender(Queue *queue):
    m_queue { queue }
{ }

}
