#include "ScheduledMessagesManager.hpp"

ScheduledMessagesManager::ScheduledMessagesManager(QueueManager *qm) : queueManager(qm) {
    messagesToSchedule.push_back(Message(1, "getDeviceStatus scheduled"));
    messagesToSchedule.push_back(Message(2, "getDeviceStatus scheduled"));
    messagesToSchedule.push_back(Message(3, "getDeviceStatus scheduled"));
}

void ScheduledMessagesManager::execute() {

    while (true){
        for (auto &msg : messagesToSchedule) {
           std::cout << "ScheduledMessagesManager::execute push scheduled message [" << msg.shortAddress << "=" << msg.text << "]" << std::endl;
           queueManager->pushScheduledMessage(msg);
           std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
}
