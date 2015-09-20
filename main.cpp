#include <iostream>

#include "subjects/receiver.h"
#include "subjects/sender.h"

#include "dispatcher.h"
#include "templatedispatcher.h"

struct Message {
    std::string body;
};

int main(int argc, char** argv) try {
    messaging::Receiver receiver;

    messaging::Sender sender = receiver;
    sender.send(Message { "dialog" });

    receiver.wait().handle<Message>([&](const Message& msg) {
        std::cout << msg.body << std::endl;
    });

    return 0;
}
catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 0;
}

