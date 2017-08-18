#ifndef SCHEDULEDMESSAGESMANAGER_H
#define SCHEDULEDMESSAGESMANAGER_H

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>

#include "Message.hpp"
#include "QueueManager.hpp"

class ScheduledMessagesManager {
public:
    ScheduledMessagesManager(QueueManager *qm);
    void execute();
private:
    QueueManager *queueManager;
    std::vector<Message> messagesToSchedule;
};

#endif
