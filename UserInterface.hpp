#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>

#include "Message.hpp"
#include "QueueManager.hpp"

class UserInterface {
public:
    UserInterface(QueueManager *qm);
    void execute();
private:
    QueueManager *queueManager;
    std::vector<Message> messagesFromUI;
};

#endif