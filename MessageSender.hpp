#ifndef MESSAGESENDER_H
#define MESSAGESENDER_H

#include <iostream>

#include "Message.hpp"
#include "QueueManager.hpp"
#include "SerialPortMock.hpp"

class MessageSender {
public:
    MessageSender(QueueManager *qm, SerialPortMock *spm);
    void execute();
private:
    QueueManager *queueManager;
    SerialPortMock *serialPortMock;
};

#endif