#include "UserInterface.hpp"

UserInterface::UserInterface(QueueManager *qm) : queueManager(qm) {
	messagesFromUI.push_back(Message(1000, "toggleFit 1 UI"));
    messagesFromUI.push_back(Message(1001, "toggleFit 2 UI"));
    messagesFromUI.push_back(Message(1002, "toggleFit 3 UI"));
}

void UserInterface::execute(){

    while (true){
        for (auto &msg : messagesFromUI){
           std::cout << "UserInterface::execute push priority message [" << msg.shortAddress << "=" << msg.text << "]" << std::endl;
           queueManager->pushPriorityMessage(msg);
           std::this_thread::sleep_for(std::chrono::seconds(7));
        }
    }
}
