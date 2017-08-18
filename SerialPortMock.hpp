#ifndef SERIALPORTMOCK_H
#define SERIALPORTMOCK_H

#include <vector>
#include <iostream>

#include "Message.hpp"

class SerialPortMock {
public:
    void sendMessage(Message message);
    Message receiveMessage();

private:
    std::vector<Message> messages;
};

#endif
