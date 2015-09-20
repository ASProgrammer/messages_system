#include <iostream>

#include "messages/message.h"
#include "strucutures/queue.h"
#include "subjects/receiver.h"
#include "subjects/sender.h"

struct Message { };

int main(int argc, char** argv) try {
    messaging::Receiver receiver;
    auto sender = messaging::Sender(receiver);
    sender.send(Message { });
}
catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 0;
}

