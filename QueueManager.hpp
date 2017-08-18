#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H

#include <queue>
#include <mutex>
#include <condition_variable>

#include "Message.hpp"

class QueueManager {
    public:
        void pushScheduledMessage(Message message);
        void pushPriorityMessage(Message message);
        Message popMessage();
    private:
        std::queue<Message> scheduledMessages;
        std::queue<Message> priorityMessages;
        std::mutex queueMutex;
        std::condition_variable cv;
};

#endif
