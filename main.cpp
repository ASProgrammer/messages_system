#include <iostream>

#include "messages/message.h"
#include "strucutures/queue.h"

struct Message { };

int main(int argc, char** argv) try {
    messaging::Queue queue;
    queue.push(Message{ });

}
catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 0;
}

