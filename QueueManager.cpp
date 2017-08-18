#include "QueueManager.hpp"

void QueueManager::pushScheduledMessage(Message message) {
     std::unique_lock<std::mutex> lock(queueMutex);
     scheduledMessages.push(std::move(message));
     lock.unlock();
     cv.notify_one();
}
void QueueManager::pushPriorityMessage(Message message) {
    std::unique_lock<std::mutex> lock(queueMutex);
    priorityMessages.push(std::move(message));
    lock.unlock();
    cv.notify_one();
}
Message QueueManager::popMessage() {
    std::unique_lock<std::mutex> lock(queueMutex);
    cv.wait(lock);

    while (true) {
    	if (!priorityMessages.empty()){
    		Message m = priorityMessages.front();
			priorityMessages.pop();
			return m;
		} else if (!scheduledMessages.empty()){
			Message m = scheduledMessages.front();
			scheduledMessages.pop();
			return m;
		}
    }
}
